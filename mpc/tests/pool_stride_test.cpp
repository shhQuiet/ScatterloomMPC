#include "../src/StatusBridge.h"
#include <cassert>
#include <memory>
#include <vector>

int main() {
 for (int rate : {44100, 48000, 96000}) {
  ScatterloomStatusBridge pool;
  pool.prepareMirror(rate);
  auto restore = std::make_unique<ScatterloomStatusBridge::Restore>();
  restore->sampleRate = rate; restore->count = 1; restore->order[0] = 8;
  restore->left[8] = {0.25f, -0.5f}; restore->right[8] = {-0.25f, 0.5f};
  pool.pendingRestore = std::move(restore);
  ScatterloomScopedStatusBridge scope(pool);
  std::vector<int> indices;
  float count = 0, captureSlot = 0;
  scatterloomApplyPendingPoolCommand(
   [&](int index, float left, float right) { indices.push_back(index); assert(left == -right); },
   [](int, int) {}, [](int, int, int, int) {}, [](int, int, int) {}, count, captureSlot);
  const int stride = rate <= 60000 ? 131072 : 262144;
  assert(indices.size() == 2 && indices[0] == 8 * stride && indices[1] == 8 * stride + 1);
  assert(count == 1 && pool.queue[0] == 8 && pool.complete[8]);
 }
}
