#pragma once
#include "StatusBridge.h"
#include <algorithm>
#include <array>

// Reads the existing pool mirror without allocating on the audio thread.
class PoolAudition {
 struct Voice { int slot=-1, position=0, end=0, fade=1; };
 std::array<Voice,9> voices {};
public:
 void reset() noexcept { for(auto &v:voices) v=Voice{}; }
 bool trigger(const ScatterloomStatusBridge& pool, int row, double sampleRate) noexcept {
  if (row<0 || row>=ScatterloomStatusBridge::slots) return false;
  const int slot=pool.queue[row];
  if (slot<0 || slot>=ScatterloomStatusBridge::slots || !pool.complete[slot] || pool.valid[slot]<=0) return false;
  const int length=std::min({pool.valid[slot],static_cast<int>(pool.audioLeft[slot].size()),static_cast<int>(pool.audioRight[slot].size())});
  if (length<=0) return false;
  voices[row]=Voice{slot,0,length,std::max(1,static_cast<int>(sampleRate*.005))};
  return true;
 }
 std::array<float,2> next(const ScatterloomStatusBridge& pool) noexcept {
  std::array<float,2> mixed {{0,0}};
  for (auto &v:voices) {
   if (v.slot<0) continue;
   if (!pool.complete[v.slot] || pool.valid[v.slot]<v.end || v.position>=v.end) { v=Voice{}; continue; }
   const float up=std::min(1.0f,static_cast<float>(v.position+1)/v.fade);
   const float down=std::min(1.0f,static_cast<float>(v.end-v.position)/v.fade);
   const float gain=std::min(up,down);
   mixed[0]+=pool.audioLeft[v.slot][v.position]*gain;
   mixed[1]+=pool.audioRight[v.slot][v.position]*gain;
   if (++v.position>=v.end) v=Voice{};
  }
  return mixed;
 }
};
