#pragma once
// MPC-only grain status and project-state mirror. Queue entries refer to physical DSP slots.
#include <algorithm>
#include <array>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <vector>
#include <memory>
#include "MarkovMatrix.h"

enum class ScatterloomEventType : std::uint8_t { capture, detection, step, grain, transition };
struct ScatterloomStatusBridge {
    static constexpr int mpcBridgeAbi = 4, slots = 9;
    std::atomic<int> poolCount {0};
    std::atomic<int> effectiveRotation {0};
    std::atomic<float> effectiveSensitivity {-1.0f};
    std::atomic<int> playingStep {-1};
    std::atomic<int> nextTransition {0};
    std::atomic<int> triggeredGrain {0};
    std::atomic<unsigned> grainTriggerSequence {0};
    std::atomic<unsigned> captureSequence {0};
    std::atomic<unsigned> removeSequence {0};
    std::atomic<unsigned> detectionSequence {0};
    std::array<int, slots> queue {{-1,-1,-1,-1,-1,-1,-1,-1,-1}};
    std::array<int,slots> valid {};
    std::array<float,slots> trimStarts {};
    std::array<float,slots> trimEnds {{1,1,1,1,1,1,1,1,1}};
    struct Restore {
        int sampleRate = 0, count = 0;
        std::array<int,slots> order {};
        std::array<std::vector<float>,slots> left, right;
    };
    std::array<std::vector<float>,slots> audioLeft, audioRight;
    std::array<bool,slots> complete {};
    int mirrorSampleRate = 44100;
    std::unique_ptr<Restore> pendingRestore;
    void prepareMirror(double sr) {
        mirrorSampleRate = static_cast<int>(std::lround(sr));
        const auto samples = static_cast<std::size_t>(std::ceil(sr * 2.05) + 8);
        for (int i=0;i<slots;++i) { audioLeft[i].resize(samples); audioRight[i].resize(samples); }
    }
    MarkovMatrix markov;
    int loomMode = 2, loomPrevious = -1;
    int trimSlot = -1, trimStart = 0, trimEnd = 0;
    bool recordingThisBlock = false;
    void capture(int physical) noexcept {
        if (physical < 0 || physical >= slots) return;
        captureSequence.fetch_add(1, std::memory_order_relaxed);
        auto prior = queue;
        queue[0] = physical;
        int dest=1;
        for (int slot : prior) if (slot >= 0 && slot != physical && dest < slots) queue[dest++] = slot;
        while (dest < slots) queue[dest++] = -1;
        valid[physical]=0; complete[physical]=false; trimStarts[physical]=0; trimEnds[physical]=1;
    }
    void accumulate(int physical, double position, double length, double left, double right) noexcept {
        if (physical < 0 || physical >= slots || position < 0 || length <= 0 || position >= length) return;
        recordingThisBlock = true;
        const int sample=static_cast<int>(position);
        if (sample >= 0 && static_cast<std::size_t>(sample) < audioLeft[physical].size()) {
            audioLeft[physical][sample]=static_cast<float>(left);
            audioRight[physical][sample]=static_cast<float>(right);
            valid[physical]=sample+1;
            if (position+1 >= length) complete[physical]=true;
        }
    }
    void remove(int row) noexcept {
        if(row<0 || row>=slots)return; int physical=queue[row];
        removeSequence.fetch_add(1, std::memory_order_relaxed);
        for(int i=row;i<slots-1;++i) queue[i]=queue[i+1]; queue[slots-1]=-1;
        if(physical>=0 && physical<slots){ valid[physical]=0; complete[physical]=false; }
    }
    void reorder(int from,int to) noexcept {
        if(from<0 || from>=slots || to<0 || to>=slots || queue[from]<0)return;
        int p=queue[from]; if(from<to) for(int i=from;i<to;++i)queue[i]=queue[i+1];
        if(from>to) for(int i=from;i>to;--i)queue[i]=queue[i-1]; queue[to]=p;
    }
    void clear() noexcept {queue.fill(-1);valid.fill(0);complete.fill(false);}
    void requestTrim(int row,float start,float end,double sampleRate) noexcept {
        if(row<0 || row>=slots || queue[row]<0)return;
        int physical=queue[row]; int maxSample=std::min(valid[physical],static_cast<int>(sampleRate*2));
        if(maxSample<16)return;
        // Positions are normalized to the common two-second timeline.
        int a=std::max(0,std::min(maxSample-16,static_cast<int>(start*sampleRate*2)));
        int b=std::max(a+16,std::min(maxSample,static_cast<int>(end*sampleRate*2)));
        trimSlot=physical;trimStart=a;trimEnd=b; trimStarts[physical]=static_cast<float>(a/(sampleRate*2)); trimEnds[physical]=static_cast<float>(b/(sampleRate*2));
    }
};
inline thread_local ScatterloomStatusBridge* scatterloomActiveBridge = nullptr;
class ScatterloomScopedStatusBridge {
    ScatterloomStatusBridge* previous;
public:
    explicit ScatterloomScopedStatusBridge(ScatterloomStatusBridge& b) noexcept : previous(scatterloomActiveBridge) { scatterloomActiveBridge=&b; }
    ~ScatterloomScopedStatusBridge() { scatterloomActiveBridge=previous; }
};
inline void scatterloomPublishStatus(double rotation,double sensitivity,double n,double,double,double) noexcept {
 if(scatterloomActiveBridge) {
  scatterloomActiveBridge->poolCount.store(std::max(0,std::min(9,static_cast<int>(n))),std::memory_order_relaxed);
  scatterloomActiveBridge->effectiveRotation.store(static_cast<int>(rotation),std::memory_order_relaxed);
  if (std::isfinite(sensitivity)) scatterloomActiveBridge->effectiveSensitivity.store(static_cast<float>(sensitivity * 0.01),std::memory_order_relaxed);
 }
}
inline void scatterloomPushEvent(ScatterloomEventType type,int value) noexcept {
 if (!scatterloomActiveBridge) return;
 if (type == ScatterloomEventType::step) scatterloomActiveBridge->playingStep.store(value, std::memory_order_relaxed);
 if (type == ScatterloomEventType::detection) scatterloomActiveBridge->detectionSequence.fetch_add(1, std::memory_order_relaxed);
}
inline void scatterloomPushGrainEvent(int,int) noexcept {}
inline void scatterloomPushTransitionEvent(int current,int next) noexcept {
 if (scatterloomActiveBridge && current>=1 && current<=9 && next>=1 && next<=9) {
  scatterloomActiveBridge->nextTransition.store(1+(current-1)*9+(next-1),std::memory_order_relaxed);
  scatterloomActiveBridge->triggeredGrain.store(current,std::memory_order_relaxed);
  scatterloomActiveBridge->grainTriggerSequence.fetch_add(1,std::memory_order_relaxed);
 }
}
inline void scatterloomBeginWaveformCapture(int p) noexcept {if(scatterloomActiveBridge)scatterloomActiveBridge->capture(p);}
inline void scatterloomAccumulateWaveform(int p,double pos,double len,double l,double r) noexcept {if(scatterloomActiveBridge)scatterloomActiveBridge->accumulate(p,pos,len,l,r);}
inline void scatterloomRemoveWaveform(int p) noexcept {if(scatterloomActiveBridge)scatterloomActiveBridge->remove(p);}
inline void scatterloomReorderWaveforms(int,int) noexcept {}
inline void scatterloomConfirmReorder(int a,int b) noexcept {if(scatterloomActiveBridge)scatterloomActiveBridge->reorder(a,b);}
inline void scatterloomClearWaveforms() noexcept {if(scatterloomActiveBridge)scatterloomActiveBridge->clear();}
template <typename A, typename B, typename C, typename D, typename Number>
inline void scatterloomApplyPendingPoolCommand(A&& writeAudio, B&& writeQueue, C&& writeMetadata,
                                               D&& writeTrim, Number& engineCount, Number& captureSlot) noexcept {
 if (!scatterloomActiveBridge) return;
 auto& b=*scatterloomActiveBridge;
 if (b.pendingRestore) {
  auto restored=std::move(b.pendingRestore);
  b.queue.fill(-1); b.valid.fill(0); b.complete.fill(false);
  for(int slot=0;slot<9;++slot) { writeMetadata(slot,0,0,0); writeTrim(slot,0,0); }
  for(int pos=0;pos<restored->count;++pos) {
   const int slot=restored->order[pos];
   const int n=static_cast<int>(restored->left[slot].size());
   const int copyCount=std::min(n,static_cast<int>(b.audioLeft[slot].size()));
   for(int i=0;i<copyCount;++i) {
    float l=restored->left[slot][i],r=restored->right[slot][i];
    writeAudio(slot*(b.mirrorSampleRate <= 60000 ? 131072 : 262144)+i,l,r); b.audioLeft[slot][i]=l; b.audioRight[slot][i]=r;
   }
   b.valid[slot]=copyCount;b.complete[slot]=true;b.queue[pos]=slot;
   writeQueue(pos,slot);writeMetadata(slot,0,copyCount,1);
   writeTrim(slot,0,std::min(copyCount,b.mirrorSampleRate*2));
  }
  for(int pos=restored->count;pos<9;++pos) writeQueue(pos,0);
  engineCount=static_cast<Number>(restored->count);
  captureSlot=0;
  for(int slot=0;slot<9;++slot) {
   if(std::find(b.queue.begin(),b.queue.begin()+restored->count,slot)==b.queue.begin()+restored->count) {captureSlot=static_cast<Number>(slot);break;}
  }
  if(restored->count==9) captureSlot=static_cast<Number>(b.queue[8]);
  b.poolCount.store(restored->count,std::memory_order_relaxed);
 }
 if (b.trimSlot>=0) {writeTrim(b.trimSlot,b.trimStart,b.trimEnd);b.trimSlot=-1;}
}
