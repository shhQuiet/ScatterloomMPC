#include "mpc_plugin.h"
#include "RNBO.h"
#include "StatusBridge.h"
#include "PoolAudition.h"
#include "RotationMath.h"
#include <cmath>
#include <array>
#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <cstring>
#include <cstdio>

extern "C" __attribute__((visibility("hidden"))) int scatterloom_mpc_bridge_abi_v4() noexcept;
static_assert(ScatterloomStatusBridge::mpcBridgeAbi == 4,
              "The MPC wrapper must use the lightweight status bridge");
// Temporary shutdown diagnostics: members are destroyed in reverse declaration order.
struct ShutdownTrace {
 const char* message;
 ~ShutdownTrace() { std::fprintf(stderr, "Scatterloom: %s\n", message); }
};
class Scatterloom : public mpc::Plugin {
ShutdownTrace afterCore {"engine destruction complete"};
RNBO::CoreObject core;
ShutdownTrace beforeCore {"beginning engine destruction"};
float last[28];
ScatterloomStatusBridge poolStatus;
std::mutex poolStateMutex;
int lastReportedPoolCount = -1;
int lastRingSteps = -1, lastRingPulses = -1, lastRingRotation = -1;
int lastVisibleStep = -2;
std::atomic<bool> clearRequested {false}, ringDirty {true};
std::atomic<bool> removeNewestRequested {false};
int removeNewestPhase = 0;
unsigned removeNewestBaseline = 0;
// Host waveform notifications must not block the real-time audio thread.
static constexpr int firstWaveParam = 28, waveParamCount = 129;
std::array<std::atomic<bool>, waveParamCount> pendingWave {};
std::atomic<bool> stopWaveNotifier {false};
std::atomic<bool> pulsesNotificationPending {false};
std::atomic<bool> poolAnimationNotificationPending {false};
std::atomic<bool> detectionNotificationPending {false};
std::atomic<bool> transitionNotificationPending {false};
std::atomic<bool> grainGlowNotificationPending {false};
unsigned lastGrainTriggerSequence = 0;
int grainGlowSamples = 0, grainGlowIndex = 0;
std::atomic<bool> rotationNotificationPending {false}, rotationBaseRestoreSeen {false};
std::atomic<float> lastRotationNormalized {0.0f};
inline static thread_local bool rotationUpdating = false;
std::array<std::atomic<bool>, 168> markovPending {};
std::array<std::atomic<bool>, 81> effectivePending {};
inline static thread_local bool markovUpdating = false;
std::recursive_mutex markovEditMutex;
std::atomic<int> markovPresetRefresh {0}, markovPresetCount {0};
unsigned lastDetectionSequence = 0;
int detectionFlashSamples = 0;
unsigned lastCaptureSequence = 0;
int poolAnimationFrame = 0;
int poolAnimationPosition = 0;
int poolAnimationLed = -1;
std::thread waveNotifier;
void runWaveNotifier() {
 int ringCursor = 0, playheadCursor = 0;
 auto nextSensitivityUpdate = std::chrono::steady_clock::now();
 auto nextMatrixUpdate = nextSensitivityUpdate;
 while (!stopWaveNotifier.load(std::memory_order_acquire)) {
  const auto now = std::chrono::steady_clock::now();
  if (now >= nextSensitivityUpdate) {
   nextSensitivityUpdate = now + std::chrono::milliseconds(250);
   if (getBool(1)) {
    const float effective = poolStatus.effectiveSensitivity.load(std::memory_order_relaxed);
    if (effective >= 0.0f) {
     const float bounded = std::max(0.0f, std::min(1.0f, effective));
     if (std::abs(get(0) - bounded) >= 0.01f && getBool(1)) {
      set(0, bounded);
      notifyHostParameterChanged(0);
     }
    }
   }
  }
  if (now >= nextMatrixUpdate) {
   nextMatrixUpdate = now + std::chrono::milliseconds(100);
   std::lock_guard<std::recursive_mutex> lock(markovEditMutex);
   MarkovMatrix m; for(int i=0;i<81;++i) m.values[i]=get(189+i);
   const int active=std::max(0,std::min(getInt(5),poolStatus.poolCount.load(std::memory_order_relaxed)));
   for(int row=0;row<9;++row) {
    const auto values=m.effectiveRow(row,active);
    for(int col=0;col<9;++col) { const int i=row*9+col;
     if(std::abs(get(369+i)-values[col])>0.00001f) {set(369+i,values[col]);effectivePending[i].store(true,std::memory_order_release);}
    }
   }
   const int selectedRow=std::clamp(getInt(351)-1,0,8), selectedCol=std::clamp(getInt(352)-1,0,8);
   const float selected=m.effectiveRow(selectedRow,active)[selectedCol];
   if(std::abs(get(353)-selected)>0.00001f) {
    markovUpdating=true; set(353,selected); markovUpdating=false;
    markovPending[353-189].store(true,std::memory_order_release);
   }
  }
  bool sent = false;
  for(int i=0;i<81 && !sent;++i) if(effectivePending[i].exchange(false,std::memory_order_acq_rel)) {notifyHostParameterChanged(369+i);sent=true;}
  int refreshCount = markovPresetRefresh.exchange(0,std::memory_order_acq_rel);
  if (refreshCount>0) {
   std::lock_guard<std::recursive_mutex> lock(markovEditMutex);
   int active=std::max(1,std::min(getInt(5),poolStatus.poolCount.load(std::memory_order_relaxed)));
   int preset=getInt(356);
   if (preset>0 && active==refreshCount && active!=markovPresetCount.load(std::memory_order_relaxed)) set(356,float(preset));
  }
  if (rotationNotificationPending.exchange(false,std::memory_order_acq_rel)) {
   notifyHostParameterChanged(8); sent = true;
  }
  if (grainGlowNotificationPending.exchange(false,std::memory_order_acq_rel)) {
   notifyHostParameterChanged(368); sent = true;
  }
  if (transitionNotificationPending.exchange(false,std::memory_order_acq_rel)) {
   notifyHostParameterChanged(357); sent = true;
  }
  if (detectionNotificationPending.exchange(false, std::memory_order_acq_rel)) {
   notifyHostParameterChanged(188); sent = true;
  }
  if (poolAnimationNotificationPending.exchange(false, std::memory_order_acq_rel)) {
   notifyHostParameterChanged(186); sent = true;
  }
  if (!sent && pulsesNotificationPending.exchange(false, std::memory_order_acq_rel)) {
   notifyHostParameterChanged(7); sent = true;
  }
  for (int n=0; n<168 && !sent; ++n) if (markovPending[n].exchange(false,std::memory_order_acq_rel)) {
   notifyHostParameterChanged(189+n); sent = true;
  }
  // Keep the two changing playhead lights ahead of static artwork updates.
  for (int scanned = 0; scanned < 32 && !sent; ++scanned) {
   int n = 61-firstWaveParam + playheadCursor;
   playheadCursor = (playheadCursor + 1) % 32;
   if (pendingWave[n].exchange(false, std::memory_order_acq_rel)) {
    notifyHostParameterChanged(firstWaveParam + n); sent = true;
   }
  }
  // Pan sliders and latching mode buttons also update off the audio thread.
  for (int n=0; n<13 && !sent; ++n) if (pendingStereo[n].exchange(false,std::memory_order_acq_rel)) {
   notifyHostParameterChanged(n < 9 ? 15+n : 157+n-9); sent = true;
  }
  // A rhythm change should not wait behind a long waveform refresh.
  for (int scanned = 0; scanned < 129 && !sent; ++scanned) {
   int n = 28-firstWaveParam + ringCursor;
   ringCursor = (ringCursor + 1) % 129;
   if (pendingWave[n].exchange(false, std::memory_order_acq_rel)) {
    notifyHostParameterChanged(firstWaveParam + n); sent = true;
   }
  }
  // Keep host redraw work widely spaced so it does not arrive in bursts.
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }
}
double lastValidTempo = 120.0;
float lastSectorFraction = -1.0f;
int lastSectorSteps = -1, lastSectorPulses = -1, lastSectorRotation = -1;
std::atomic<int> requestedStereoMode {0};
std::array<std::atomic<bool>, 13> pendingStereo {};
int lastStereoMode = -1, lastStereoCount = -1;
std::array<int,9> lastStereoQueue {{-2,-2,-2,-2,-2,-2,-2,-2,-2}};
std::array<std::vector<float>, 2> dryInput;
std::array<std::vector<float>, 2> auditionBuffer;
PoolAudition poolAudition;
std::atomic<unsigned> pendingAudition {0};
float stoppedDryBlend = 0.0f;
bool transportBlendReady = false;

public:
static std::vector<std::string> divisions() {
 return {"2 Bars", "1 Bar", "1/2", "1/2T", "1/4", "1/4T", "1/4.", "1/8", "1/8T", "1/8.", "1/16", "1/16T", "1/16.", "1/32"};
}
static mpc::PluginInfo info(){ mpc::PluginInfo i; i.name="Scatterloom"; i.vendor="Elsewave"; i.uniqueId=MPC_FOURCC('S','E','Z','Q'); i.version=200; /* 0.2.0.0 */ i.isInstrument=false; i.numInputs=2; i.numOutputs=2; return i; }
Scatterloom():mpc::Plugin(info()) {
// Force a link-time dependency on the guarded MPC RNBO translation unit.
(void) scatterloom_mpc_bridge_abi_v4();
addParam(mpc::floatParam("sensitivity","Sensitivity",0.0f,1.0f,0.35f));
addParam(mpc::boolParam("autoSensitivity", "Auto Sens", true));
addParam(mpc::boolParam("captureOn", "Capture", true));
addParam(mpc::floatParam("grain","Grain Length",0.0f,1.0f,0.33f));
addParam(mpc::floatParam("attack","Attack",0.0f,1.0f,0.0f));
addParam(mpc::intParam("grainCount", "Recent Grains", 1, 9, 5));
addParam(mpc::intParam("steps", "Steps", 1, 32, 16));
addParam(mpc::intParam("pulses", "Pulses", 0, 32, 5));
addParam(mpc::intParam("rotation", "Rotate", 0, 31, 0));
addParam(mpc::floatParam("feedback","Loop Feedback",0.0f,1.15f,0.35f));
addParam(mpc::floatParam("mixAmount","Mix",0.0f,1.0f,0.5f));
addParam(mpc::floatParam("reverseProbability","Reverse Chance",0.0f,1.0f,0.0f));
addParam(mpc::boolParam("clearPool", "Clear Pool", false));
addParam(mpc::choiceParam("division", "Division", divisions(), 10));
addParam(mpc::choiceParam("rotationInterval", "Rotation Mode", {"Manual", "1 Beat", "2 Beats", "3 Beats", "4 Beats", "6 Beats", "8 Beats", "12 Beats", "16 Beats", "24 Beats", "32 Beats", "48 Beats", "64 Beats", "96 Beats"}, 0));
addParam(mpc::floatParam("grainPan0","Grain Pan 1",-1.0f,1.0f,-0.5f));
addParam(mpc::floatParam("grainPan1","Grain Pan 2",-1.0f,1.0f,0.5f));
addParam(mpc::floatParam("grainPan2","Grain Pan 3",-1.0f,1.0f,-0.25f));
addParam(mpc::floatParam("grainPan3","Grain Pan 4",-1.0f,1.0f,0.25f));
addParam(mpc::floatParam("grainPan4","Grain Pan 5",-1.0f,1.0f,0.0f));
addParam(mpc::floatParam("grainPan5","Grain Pan 6",-1.0f,1.0f,-0.375f));
addParam(mpc::floatParam("grainPan6","Grain Pan 7",-1.0f,1.0f,0.375f));
addParam(mpc::floatParam("grainPan7","Grain Pan 8",-1.0f,1.0f,-0.125f));
addParam(mpc::floatParam("grainPan8","Grain Pan 9",-1.0f,1.0f,0.125f));
addParam(mpc::choiceParam("grainSelectionMode", "Order Engine", {"Played", "Random", "Neighbors", "Wander", "Repeat", "Bounce", "Surprise"}, 0));
addParam(mpc::choiceParam("loopDivision", "Loop Time", divisions(), 4));
addParam(mpc::floatParam("timingOffset","Grain Start",-0.2f,0.2f,0.0f));
{ auto status = mpc::intParam("poolCount", "", 0, 9, 0); status.automatable = false; addParam(status); }
// Read-only indicators appended after existing parameters to preserve indices.
for (int i=0; i<32; ++i) {
 auto p = mpc::boolParam(("rhythmStep"+std::to_string(i)).c_str(), "", false);
 p.automatable=false; addParam(p);
}
{ auto p=mpc::floatParam("rhythmArc", "", 0, 1, 0); p.automatable=false; addParam(p); }
for (int i=0; i<32; ++i) {
 auto p=mpc::boolParam(("playhead"+std::to_string(i)).c_str(), "", false);
 p.automatable=false; addParam(p);
}
for (int i=0; i<64; ++i) {
 auto p=mpc::floatParam(("rhythmSector"+std::to_string(i)).c_str(), "", 0, 1, 0);
 p.automatable=false; addParam(p);
}
for (const char* name : {"Center", "Left to Right", "Right to Left", "Spread"}) {
 std::string id = std::string("stereoMode") + name;
 addParam(mpc::boolParam(id.c_str(), name, std::string(name) == "Spread"));
}
addParam(mpc::boolParam("confirmClear", "Confirm Clear", true));
addParam(mpc::boolParam("playEnabled", "Play", true));
// Retain retired parameter positions for compatibility with saved projects.
{ auto p=mpc::intParam("reserved163", "", 0, 5, 0); p.automatable=false; addParam(p); }
{ auto p=mpc::intParam("reserved164", "", 0, 1224, 0); p.automatable=false; addParam(p); }
{ auto p=mpc::intParam("reserved165", "", 0, 42874, 0); p.automatable=false; addParam(p); }
for (int i=166; i<=185; ++i) { auto id=std::string("reserved")+std::to_string(i); auto p=mpc::boolParam(id.c_str(), "", false); p.automatable=false; addParam(p); }
{ auto p=mpc::intParam("poolAnimation", "", 0, 9, 0); p.automatable=false; addParam(p); }
{ auto p=mpc::boolParam("removeNewest", "", false); p.automatable=false; addParam(p); }
{ auto p=mpc::boolParam("detectionFlash", "", false); p.automatable=false; addParam(p); }
// Stable host parameters keep the matrix with each plugin instance.
for (int row=0; row<9; ++row) for (int col=0; col<9; ++col) {
 auto id=std::string("markovCell")+std::to_string(row*9+col);
 auto p=mpc::floatParam(id.c_str(), "", 0.0f, 1.0f, col==(row==0?8:row-1)?1.0f:0.0f);
 p.automatable=false; addParam(p);
}
for (int i=0;i<81;++i) {auto id=std::string("markovSelect")+std::to_string(i);auto p=mpc::boolParam(id.c_str(), "", false);p.automatable=false;addParam(p);}
addParam(mpc::intParam("markovRow", "Current Grain", 1, 9, 1));
addParam(mpc::intParam("markovColumn", "Next Grain", 1, 9, 1));
addParam(mpc::floatParam("markovValue", "Probability", 0.0f, 1.0f, 0.0f));
addParam(mpc::boolParam("markovSequential", "As Played", false));
addParam(mpc::boolParam("markovRandom", "Random", false));
addParam(mpc::choiceParam("markovPreset", "Patterns", {"Custom", "As Played", "Random", "Neighbors", "Wander", "Repeat", "Bounce", "Surprise", "Stay or Next", "Skip Ahead", "Reverse", "Drift Forward"}, 0));
{ auto p=mpc::intParam("markovTransition", "", 0, 81, 0); p.automatable=false; addParam(p); }
for(int i=0;i<9;++i) {auto id=std::string("poolPad")+std::to_string(i);auto p=mpc::boolParam(id.c_str(), "", false);p.automatable=false;addParam(p);}
{ auto p=mpc::intParam("rotationBase", "", 0, 31, 0); p.automatable=false; addParam(p); }
{ auto p=mpc::intParam("grainGlow", "", 0, 45, 0); p.automatable=false; addParam(p); }
for(int i=0;i<81;++i) {auto id=std::string("effectiveMarkovCell")+std::to_string(i);auto p=mpc::floatParam(id.c_str(),"",0.0f,1.0f,0.0f);p.automatable=false;addParam(p);}
for(float &v:last) v=NAN;
}
// The RNBO parameters use normalized units; display values in musical units.
bool formatValue(int index, float value, std::string& out) override {
 char text[32];
 switch(index) {
  case 3: std::snprintf(text,sizeof(text),"%.0f ms",(0.02f + 1.98f * value * value) * 1000.0f); break;
  case 4: std::snprintf(text,sizeof(text),"%.0f ms",value * 1000.0f); break;
  case 26: std::snprintf(text,sizeof(text),"%+.0f ms",value * 1000.0f); break;
  case 353: case 0: case 9: case 10: case 11:
   std::snprintf(text,sizeof(text),"%.0f%%",value * 100.0f); break;
  default: return false;
 }
 out = text; return true;
}
~Scatterloom() override {
 std::fprintf(stderr, "Scatterloom: closing; stopping display notifier\n");
 stopWaveNotifier.store(true, std::memory_order_release);
 if (waveNotifier.joinable()) waveNotifier.join();
 std::fprintf(stderr, "Scatterloom: display notifier stopped\n");
}
void prepare(double sr,int block) override {
 lastDetectionSequence = poolStatus.detectionSequence.load(std::memory_order_relaxed);
 detectionFlashSamples = 0; set(188, 0.0f); detectionNotificationPending.store(true, std::memory_order_release);
 poolAnimationFrame = 0; poolAnimationPosition = 0; poolAnimationLed = -1;
 lastCaptureSequence = poolStatus.captureSequence.load(std::memory_order_relaxed);
 set(186, 0.0f); poolAnimationNotificationPending.store(true, std::memory_order_release);
 for (auto& channel : dryInput) channel.resize(std::max(block, 8192));
 for (auto& channel : auditionBuffer) channel.resize(std::max(block, 8192));
 poolAudition.reset(); pendingAudition.store(0,std::memory_order_relaxed);
 { std::lock_guard<std::mutex> lock(poolStateMutex); poolStatus.prepareMirror(sr); }
 transportBlendReady = false;
 if (!waveNotifier.joinable()) {
  stopWaveNotifier.store(false, std::memory_order_relaxed);
  waveNotifier = std::thread([this] { runWaveNotifier(); });
 }
 core.prepareToProcess(sr,block); for(float &v:last)v=NAN;
 lastReportedPoolCount=-1;
}
// Versioned project grain data; project saving may pause processing while the
// snapshot is copied. The host calls these methods outside the audio callback.
void saveExtraState(std::vector<uint8_t>& out) override {
 std::fprintf(stderr, "Scatterloom: saving grain state\n");
 std::lock_guard<std::mutex> lock(poolStateMutex);
 auto put32=[&](uint32_t v) {for(int j=0;j<4;++j) out.push_back(static_cast<uint8_t>(v>>(8*j)));};
 out.insert(out.end(), {'S','L','P','2'});
 put32(static_cast<uint32_t>(poolStatus.mirrorSampleRate));
 int count=0; for(int pos=0;pos<9;++pos) {
  const int slot=poolStatus.queue[pos];
  if(slot>=0 && slot<9 && poolStatus.complete[slot] && poolStatus.valid[slot]>0) ++count;
 }
 put32(static_cast<uint32_t>(count));
 for(int pos=0;pos<9;++pos) {
  int slot=poolStatus.queue[pos];
  if(slot<0 || slot>=9 || !poolStatus.complete[slot] || poolStatus.valid[slot]<=0) continue;
  int samples=std::min(poolStatus.valid[slot],static_cast<int>(poolStatus.audioLeft[slot].size()));
  put32(static_cast<uint32_t>(slot)); put32(static_cast<uint32_t>(samples));
  for(int i=0;i<samples;++i) for(float sample : {poolStatus.audioLeft[slot][i],poolStatus.audioRight[slot][i]}) {
   uint32_t bits;std::memcpy(&bits,&sample,sizeof(bits));put32(bits);
  }
 }
 for (int i=0;i<81;++i) { float value=get(189+i); uint32_t bits; std::memcpy(&bits,&value,4); put32(bits); }
 std::fprintf(stderr, "Scatterloom: grain state saved\n");
}
void loadExtraState(const uint8_t* data, size_t size) override {
 if (!data || size<12) return;
 const bool hasMatrix=std::memcmp(data,"SLP2",4)==0;
 if (!hasMatrix && std::memcmp(data,"SLP1",4)!=0) return;
 size_t pos=4;
 auto get32=[&](uint32_t& v) {if(pos+4>size)return false;v=0;for(int j=0;j<4;++j)v|=uint32_t(data[pos++])<<(8*j);return true;};
 uint32_t sr=0,count=0;
 if(!get32(sr)||!get32(count)||sr<8000||sr>192000||count>9) return;
 auto restored=std::make_unique<ScatterloomStatusBridge::Restore>();
 restored->sampleRate=static_cast<int>(sr);restored->count=static_cast<int>(count);
 std::array<bool,9> used {};
 for(uint32_t row=0;row<count;++row) {
  uint32_t slot=0,n=0;
  if(!get32(slot)||!get32(n)||slot>=9||used[slot]||n==0||n>524286||n>size/8 || size-pos<static_cast<size_t>(n)*8) return;
  used[slot]=true;restored->order[row]=static_cast<int>(slot);
  restored->left[slot].resize(n);restored->right[slot].resize(n);
  for(uint32_t i=0;i<n;++i) {
   uint32_t left=0,right=0;if(!get32(left)||!get32(right))return;
   std::memcpy(&restored->left[slot][i],&left,4);std::memcpy(&restored->right[slot][i],&right,4);
   if(!std::isfinite(restored->left[slot][i])||!std::isfinite(restored->right[slot][i]))return;
  }
 }
 std::array<float,81> matrix {};
 if (hasMatrix) for (float &value:matrix) {
  uint32_t bits=0; if(!get32(bits)) return; std::memcpy(&value,&bits,4);
  if(!std::isfinite(value) || value<0.0f || value>1.0f) return;
 }
 if(pos != size) return;
 std::lock_guard<std::mutex> lock(poolStateMutex);
 // Standalone MPC runs at 44.1 kHz; reject mismatched audio rather than
 // silently playing it at the wrong rate.
 if(restored->sampleRate != poolStatus.mirrorSampleRate) return;
 // Older project states do not have the separate manual base parameter.
 if (!rotationBaseRestoreSeen.exchange(false,std::memory_order_acq_rel)) {
  rotationUpdating=true; set(367,get(8)); rotationUpdating=false;
 }
 rotationUpdating=true; setNormalised(8,lastRotationNormalized.load(std::memory_order_acquire)); rotationUpdating=false;
 if (hasMatrix) {
  markovUpdating=true;
  for (int i=0;i<81;++i) { set(189+i,matrix[i]); markovPending[i].store(true,std::memory_order_release); }
  markovUpdating=false;
 }
 poolStatus.pendingRestore=std::move(restored);
}
// Latch momentary touches even when press and release both occur between
// audio blocks. The audio thread consumes each pending action once.
void parameterChanged(int index, float value) override {
 if (!rotationUpdating && index==367) rotationBaseRestoreSeen.store(true,std::memory_order_release);
 if (!rotationUpdating && index==8) {
  lastRotationNormalized.store(getNormalised(8),std::memory_order_release);
  int target=static_cast<int>(std::lround(value));
  int base=target;
  if (getInt(14)>0) base=scatterloomRotationBaseForTarget(getInt(367),
    poolStatus.effectiveRotation.load(std::memory_order_relaxed), target, getInt(6));
  rotationUpdating=true; set(367,float(base)); rotationUpdating=false;
 }
 if (!rotationUpdating && index==14 && value<0.5f) {
  rotationUpdating=true; set(8,get(367)); rotationUpdating=false;
  rotationNotificationPending.store(true,std::memory_order_release);
 }
 if (index>=358 && index<=366 && value>0.5f) pendingAudition.fetch_or(1u<<(index-358),std::memory_order_release);
 if (!markovUpdating && index >= 270 && index <= 356) {
  std::lock_guard<std::recursive_mutex> lock(markovEditMutex);
  markovUpdating = true;
  auto update = [this](int i, float v) { set(i,v); if(i>=189 && i<=356) markovPending[i-189].store(true,std::memory_order_release); };
  int row=std::clamp(getInt(351)-1,0,8), col=std::clamp(getInt(352)-1,0,8);
  auto effectiveValue = [this](int r,int c) { MarkovMatrix m; for(int i=0;i<81;++i)m.values[i]=get(189+i); int active=std::max(0,std::min(getInt(5),poolStatus.poolCount.load(std::memory_order_relaxed))); return m.effectiveRow(r,active)[c]; };
  if (index>=270 && index<=350 && value>0.5f) {
   int cell=index-270; row=cell/9; col=cell%9;
   update(351,float(row+1)); update(352,float(col+1)); update(353,effectiveValue(row,col));
  } else if (index==351 || index==352) {
   update(353,effectiveValue(row,col));
  } else if (index==353) {
   MarkovMatrix m; for(int i=0;i<81;++i)m.values[i]=get(189+i);
   int active=std::max(0,std::min(getInt(5),poolStatus.poolCount.load(std::memory_order_relaxed)));
   m.setEffectiveProbability(row,col,active,value);
   for(int c=0;c<9;++c) update(189+row*9+c,m.values[row*9+c]);
   update(353,m.effectiveRow(row,active)[col]);
   update(356,0.0f);
  } else if (((index==354 || index==355) && value>0.5f) || (index==356 && value>=0.5f)) {
   MarkovMatrix m; const int preset = index==354 ? 1 : (index==355 ? 2 : int(value)); int active=std::max(1,std::min(getInt(5),poolStatus.poolCount.load(std::memory_order_relaxed)));
   m.preset(preset,active); markovPresetCount.store(active,std::memory_order_relaxed);
   for(int i=0;i<81;++i)update(189+i,m.values[i]);
   update(353,m.values[row*9+col]);
  }
  markovUpdating = false;
 }

 if (index == 187 && value > 0.5f) removeNewestRequested.store(true, std::memory_order_release);
 if ((index == 6 || index == 7) && getInt(7) > getInt(6)) {
  set(7, static_cast<float>(getInt(6)));
  pulsesNotificationPending.store(true, std::memory_order_release);
 }
 // Display values are derived state: restore them after any host write.
 if (index >= 28 && index <= 156) ringDirty.store(true, std::memory_order_relaxed);
 if (value > 0.5f) {
  if (index >= 157 && index <= 160) requestedStereoMode.store(index - 156, std::memory_order_relaxed);
  if (index == 12) clearRequested.store(true, std::memory_order_relaxed);
 }
}
// The host calls reset after state load and on resume. Rebase the selection
// so a restored selection is not mistaken for a tap and auditioned.
void reset() override {
 pendingAudition.store(0,std::memory_order_relaxed); poolAudition.reset();
 clearRequested.store(false, std::memory_order_relaxed);
 removeNewestRequested.store(false, std::memory_order_relaxed);
 removeNewestPhase = 0;
 lastReportedPoolCount = -1;
 lastRingSteps = lastRingPulses = lastRingRotation = -1;
 lastVisibleStep = -2;
}
void process(mpc::ProcessContext& c) override {
// Latching modes operate on pool order; manual mode retains slider values.
int modeRequest = requestedStereoMode.exchange(0, std::memory_order_relaxed);
if (modeRequest > 0) for (int i=0; i<4; ++i) {
 if (i != modeRequest-1 && getBool(157+i)) {set(157+i,0);pendingStereo[9+i].store(true,std::memory_order_release);}
}
int stereoMode = 0;
for (int i=0; i<4; ++i) if (getBool(157+i)) stereoMode=i+1;
const int stereoCount = std::max(0,std::min(9,poolStatus.poolCount.load(std::memory_order_relaxed)));
if (stereoMode != 0) {
 for (int i=0; i<stereoCount; ++i) {
  float pan=0;
  if (stereoCount > 1 && (stereoMode == 2 || stereoMode == 3)) {
   pan = -1.0f + 2.0f*i/(stereoCount-1);
   if (stereoMode == 3) pan=-pan;
  } else if (stereoCount > 1 && stereoMode == 4) {
   const int pairs=(stereoCount+1)/2;
   pan = (i%2 == 0 ? -1.0f : 1.0f) * static_cast<float>(i/2+1)/pairs;
  }
  if (std::abs(get(15+i)-pan)>0.0001f) {set(15+i,pan);pendingStereo[i].store(true,std::memory_order_release);}
 }
}
// Positions without an occupied grain are centered and cannot be edited.
for (int i=stereoCount;i<9;++i) if (std::abs(get(15+i))>0.0001f) {
 set(15+i,0.0f);pendingStereo[i].store(true,std::memory_order_release);
}
lastStereoMode=stereoMode;lastStereoCount=stereoCount;lastStereoQueue=poolStatus.queue;
float panByPhysical[9];
for (int i=0;i<9;++i) panByPhysical[i]=get(15+i);
for (int row=0;row<stereoCount;++row) {
 int physical=poolStatus.queue[row];
 if (physical>=0 && physical<9) panByPhysical[physical]=get(15+row);
}
for(int n=0;n<28;n++){
 float v;
 if(n == 8) v=get(367);
 else if(n == 13) {
  // Always release Clear for a block between presses so the engine sees an edge.
  v = last[n] == 1.0f ? 0.0f : (clearRequested.exchange(false, std::memory_order_relaxed) ? 1.0f : 0.0f);
 } else if (n == 25) v=2.0f;
 else if (n >= 16 && n <= 24) v=panByPhysical[n-16];
 else if (n == 11) v=1.0f;
 else v=get(n < 11 ? n : n-1);
 if(v!=last[n]){core.setParameterValue(n,v);last[n]=v;}
}
// Pulse the engine's existing remove parameter. If a simultaneous capture
// prevents the removal edge, retry only after releasing it for a block.
if (removeNewestRequested.exchange(false, std::memory_order_acq_rel) && removeNewestPhase == 0 &&
    poolStatus.poolCount.load(std::memory_order_relaxed) > 0) {
 removeNewestBaseline = poolStatus.removeSequence.load(std::memory_order_relaxed);
 removeNewestPhase = 1;
}
if (removeNewestPhase != 0) {
 if (poolStatus.removeSequence.load(std::memory_order_relaxed) != removeNewestBaseline ||
     poolStatus.poolCount.load(std::memory_order_relaxed) == 0) {
  core.setParameterValue(28, 0.0f); removeNewestPhase = 0;
 } else if (removeNewestPhase == 1) {
  core.setParameterValue(28, 1.0f); removeNewestPhase = 2;
 } else {
  core.setParameterValue(28, 0.0f); removeNewestPhase = 1;
 }
}
// The MPC can process in-place, so preserve the live input before RNBO
// overwrites its buffers. All storage was allocated during prepare().
const bool canPassThrough = c.numFrames <= static_cast<int>(dryInput[0].size());
if (canPassThrough) for (int ch=0; ch<2; ++ch)
 for (int n=0; n<c.numFrames; ++n) dryInput[ch][n] = c.inputs[ch][n];
const bool scatterloomPlaying = c.transport.playing && getBool(162);
auto t=core.getCurrentTime();
if(c.transport.tempoValid) core.scheduleEvent(RNBO::TempoEvent(t,c.transport.bpm));
if(c.transport.ppqValid) core.scheduleEvent(RNBO::BeatTimeEvent(t,c.transport.ppqPos));
core.scheduleEvent(RNBO::TransportEvent(t,scatterloomPlaying ? RNBO::TransportState::RUNNING : RNBO::TransportState::STOPPED));
{
 // Suppress waveform notifications while the engine is recording grains.
 poolStatus.recordingThisBlock = false;
 std::lock_guard<std::mutex> lock(poolStateMutex);
 for (int i=0; i<81; ++i) poolStatus.markov.values[i] = get(189+i);
 ScatterloomScopedStatusBridge scope(poolStatus);
 core.process(c.inputs,2,c.outputs,2,c.numFrames);
 if (c.numFrames<=static_cast<int>(auditionBuffer[0].size())) {
  const unsigned requests=pendingAudition.exchange(0,std::memory_order_acq_rel);
  for (int row=0;row<9;++row) if(requests & (1u<<row)) poolAudition.trigger(poolStatus,row,c.sampleRate);
  if (poolAudition.active()) {
   for(int n=0;n<c.numFrames;++n) {
    auto frame=poolAudition.next(poolStatus);
    auditionBuffer[0][n]=frame[0]; auditionBuffer[1][n]=frame[1];
   }
  } else {
   std::fill_n(auditionBuffer[0].begin(), c.numFrames, 0.0f);
   std::fill_n(auditionBuffer[1].begin(), c.numFrames, 0.0f);
  }
 }
}
// Five visual steps approximate a short linear fade without audio-rate redraws.
const unsigned grainSequence = poolStatus.grainTriggerSequence.load(std::memory_order_relaxed);
if (scatterloomPlaying && grainSequence != lastGrainTriggerSequence) {
 lastGrainTriggerSequence = grainSequence;
 grainGlowIndex = poolStatus.triggeredGrain.load(std::memory_order_relaxed);
 grainGlowSamples = std::max(1, int(c.sampleRate * 0.2));
}
const int glowPoolCount = poolStatus.poolCount.load(std::memory_order_relaxed);
if (!scatterloomPlaying || glowPoolCount <= 0 || grainGlowIndex > glowPoolCount) {
 grainGlowSamples = 0;
 lastGrainTriggerSequence = grainSequence;
}
const int glowDuration = std::max(1, int(c.sampleRate * 0.2));
const int glowLevel = grainGlowSamples > 0 ? std::min(5, 1 + (grainGlowSamples - 1) * 5 / glowDuration) : 0;
const int glowValue = glowLevel && grainGlowIndex >= 1 && grainGlowIndex <= 9 ? 1 + (grainGlowIndex-1)*5 + (glowLevel-1) : 0;
if (getInt(368) != glowValue) { set(368, float(glowValue)); grainGlowNotificationPending.store(true,std::memory_order_release); }
grainGlowSamples = std::max(0, grainGlowSamples - c.numFrames);
if (!scatterloomPlaying) poolStatus.nextTransition.store(0,std::memory_order_relaxed);
const int transition=poolStatus.nextTransition.load(std::memory_order_relaxed);
if (getInt(357)!=transition) {set(357,float(transition)); transitionNotificationPending.store(true,std::memory_order_release);}
// Refresh only when the rhythm changes, not on every audio block.
if (c.transport.tempoValid && std::isfinite(c.transport.bpm) && c.transport.bpm > 0.0)
 lastValidTempo = c.transport.bpm;
const int ringSteps = std::max(1,std::min(32,getInt(6)));
const int ringPulses = std::max(0,std::min(ringSteps,getInt(7)));
const int ringRotation = ((poolStatus.effectiveRotation.load(std::memory_order_relaxed) % ringSteps) + ringSteps) % ringSteps;
if (getInt(14)>0 && getInt(8)!=ringRotation) {
 rotationUpdating=true; set(8,float(ringRotation)); rotationUpdating=false;
 rotationNotificationPending.store(true,std::memory_order_release);
}
const bool displayDirty = ringDirty.exchange(false, std::memory_order_relaxed);
if (displayDirty || ringSteps != lastRingSteps || ringPulses != lastRingPulses || ringRotation != lastRingRotation) {
 for (int i=0;i<32;++i) {
  const float active = (i < ringSteps && (((i + ringRotation) % ringSteps) * ringPulses) % ringSteps < ringPulses) ? 1.0f : 0.0f;
  const int index = 28 + i;
  if (get(index) != active) { set(index,active); pendingWave[index-firstWaveParam].store(true,std::memory_order_release); }
 }
 lastRingSteps=ringSteps; lastRingPulses=ringPulses; lastRingRotation=ringRotation;
}
// The engine reports rotated step numbers. Convert them to ring positions.
const int currentStep = scatterloomPlaying ? poolStatus.playingStep.load(std::memory_order_relaxed) : -1;
const int visibleStep = currentStep >= 0 ? (currentStep - ringRotation + ringSteps) % ringSteps : -1;
if (displayDirty || visibleStep != lastVisibleStep) {
 for (int i=0; i<32; ++i) {
  const int index=61+i; const float active = i == visibleStep ? 1.0f : 0.0f;
  if (get(index) != active) { set(index, active); pendingWave[index-firstWaveParam].store(true,std::memory_order_release); }
 }
 lastVisibleStep = visibleStep;
}
// Arc length is grain duration relative to the entire rhythm cycle.
static constexpr double rates[] = {0.125, 0.25, 0.5, 0.75, 1.0, 1.5, 2.0/3.0, 2.0, 3.0, 4.0/3.0, 4.0, 6.0, 8.0/3.0, 8.0};
const int rateIndex = std::max(0,std::min(13,getInt(13)));
const double grain = get(3);
const double grainSeconds = 0.02 + 1.98 * grain * grain;
const float fullArcFraction = static_cast<float>(grainSeconds * lastValidTempo * rates[rateIndex] / (60.0 * ringSteps));
const float arcFraction = std::min(1.0f, fullArcFraction);
if (std::abs(get(60) - arcFraction) >= 1.0f/1024.0f) {
 set(60, arcFraction);
 pendingWave[60-firstWaveParam].store(true,std::memory_order_release);
}
// The ring uses 64 short image segments. Only recalculate when its pattern
// or the duration relative to the cycle changes; never generate artwork in audio.
if (displayDirty || lastSectorSteps != ringSteps || lastSectorPulses != ringPulses || lastSectorRotation != ringRotation ||
    std::abs(lastSectorFraction-fullArcFraction) >= 1.0f/1024.0f) {
 bool activeSteps[32] = {}; int nextGaps[32] = {}; double starts[32] = {};
 for (int i=0; i<ringSteps; ++i) {
  activeSteps[i] = (((i+ringRotation)%ringSteps)*ringPulses)%ringSteps < ringPulses;
  starts[i] = static_cast<double>(i)/ringSteps;
 }
 for (int i=0; i<ringSteps; ++i) if (activeSteps[i])
  for (int gap=1; gap<ringSteps; ++gap) if (activeSteps[(i+gap)%ringSteps]) { nextGaps[i]=gap; break; }
 const int wholeGrains = static_cast<int>(fullArcFraction);
 const double partialGrain = fullArcFraction - std::floor(fullArcFraction);
 for (int segment=0; segment<64; ++segment) {
  const double t=(segment+0.5)/64.0; int grains=0, ribbon=0;
  for (int i=0; i<ringSteps; ++i) {
   if (!activeSteps[i]) continue;
   double delta=t-starts[i]; if (delta<0) delta+=1.0;
   grains += wholeGrains;
   if (delta < partialGrain) ++grains;
   const int gap=nextGaps[i];
   if (gap>1) {
    const double end=static_cast<double>(gap)/ringSteps;
    if (delta>0.012 && delta<end-0.012) {
     const int level=std::max(1,std::min(7,static_cast<int>((1.0-delta/end)*7.0)+1));
     ribbon=std::max(ribbon,level);
    }
   }
  }
  const int ribbonLevel = (ribbon * 3 + 3) / 7;
  const float value=static_cast<float>(std::min(grains,5)+6*ribbonLevel)/23.0f;
  const int index=93+segment;
  if (get(index)!=value) {set(index,value);pendingWave[index-firstWaveParam].store(true,std::memory_order_release);}
 }
 lastSectorSteps=ringSteps;lastSectorPulses=ringPulses;lastSectorRotation=ringRotation;lastSectorFraction=fullArcFraction;
}
const int poolCount = poolStatus.poolCount.load(std::memory_order_relaxed);
const int presetActive = std::max(1,std::min(getInt(5),poolCount));
if (getInt(356)>0 && presetActive!=markovPresetCount.load(std::memory_order_relaxed))
 markovPresetRefresh.store(presetActive,std::memory_order_release);
const unsigned detectionSequence = poolStatus.detectionSequence.load(std::memory_order_relaxed);
if (detectionSequence != lastDetectionSequence) {
 lastDetectionSequence = detectionSequence;
 detectionFlashSamples = std::max(1, static_cast<int>(c.sampleRate * 0.15));
} else detectionFlashSamples = std::max(0, detectionFlashSamples - c.numFrames);
const bool detectionLit = detectionFlashSamples > 0;
if (getBool(188) != detectionLit) {
 set(188, detectionLit ? 1.0f : 0.0f);
 detectionNotificationPending.store(true, std::memory_order_release);
}
const unsigned captureSequence = poolStatus.captureSequence.load(std::memory_order_relaxed);
if (captureSequence != lastCaptureSequence) {
 lastCaptureSequence = captureSequence;
 poolAnimationFrame = 1;
 poolAnimationPosition = 0;
 poolAnimationLed = poolCount < 9 ? std::max(0, poolCount - 1) : -1;
}
if (poolAnimationFrame > 0) {
 const int duration = std::max(1, static_cast<int>(c.sampleRate * 0.045));
 poolAnimationFrame += c.numFrames;
 while (poolAnimationFrame > duration) { poolAnimationFrame -= duration; ++poolAnimationPosition; }
 const int total = poolAnimationLed < 0 ? 9 : 3;
 const int led = poolAnimationPosition >= total ? 0 :
   (poolAnimationLed < 0 ? 9 - poolAnimationPosition : (poolAnimationPosition % 2 == 0 ? poolAnimationLed + 1 : 0));
 if (getInt(186) != led) { set(186, static_cast<float>(led)); poolAnimationNotificationPending.store(true, std::memory_order_release); }
 if (poolAnimationPosition >= total) poolAnimationFrame = 0;
}
if (poolCount != lastReportedPoolCount || getInt(27) != poolCount) {
 set(27, static_cast<float>(poolCount));
 // Changes are infrequent (capture/remove/clear), unlike audio-rate meters.
 notifyHostParameterChanged(27);
 lastReportedPoolCount = poolCount;
}
// Crossfade on transport transitions to avoid a click; continue processing
// internally so capture and existing engine state remain available.
const float targetDry = scatterloomPlaying ? 0.0f : 1.0f;
if (!transportBlendReady) { stoppedDryBlend = targetDry; transportBlendReady = true; }
const float fadeStep = static_cast<float>(1.0 / std::max(1.0, c.sampleRate * 0.005));
for (int n=0; n<c.numFrames; ++n) {
 if (stoppedDryBlend < targetDry) stoppedDryBlend = std::min(targetDry, stoppedDryBlend + fadeStep);
 else if (stoppedDryBlend > targetDry) stoppedDryBlend = std::max(targetDry, stoppedDryBlend - fadeStep);
 for (int ch=0; ch<2; ++ch) {
  const float processed = c.outputs[ch][n];
  const float mixed = canPassThrough ? processed * (1.0f-stoppedDryBlend) + dryInput[ch][n] * stoppedDryBlend : processed;
  const float audition = c.numFrames <= static_cast<int>(auditionBuffer[ch].size()) ? auditionBuffer[ch][n] : 0.0f;
  c.outputs[ch][n] = mixed + audition;
 }
}
}
};
// Q-Link and touchscreen edits are locked while an automatic mode is active.
static void stereoSetParameter(AEffect* effect, VstInt32 index, float value) {
 auto* plugin=static_cast<Scatterloom*>(effect->object);
 if (index == 0 && plugin->getBool(1)) return;
 if (index >= 15 && index <= 23) {
  if (index-15 >= plugin->getInt(27)) return;
  for (int i=157; i<=160; ++i) if (plugin->getBool(i)) return;
 }
 mpc::detail::setParameter(effect,index,value);
}
extern "C" MPC_EXPORT AEffect* VSTPluginMain(audioMasterCallback host) {
 if (host && host(nullptr,audioMasterVersion,0,0,nullptr,0.0f)==0) return nullptr;
 AEffect* effect=mpc::detail::createEffect(new Scatterloom(),host);
 if (effect) effect->setParameter=&stereoSetParameter;
 return effect;
}
#if defined(__APPLE__)
extern "C" MPC_EXPORT AEffect* main_macho(audioMasterCallback host) { return VSTPluginMain(host); }
#endif
