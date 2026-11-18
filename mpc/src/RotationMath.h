#pragma once
#include <algorithm>
inline int scatterloomRotationBaseForTarget(int base, int effective, int target, int steps) noexcept {
 steps=std::clamp(steps,1,32);
 auto wrap=[steps](int n){return ((n%steps)+steps)%steps;};
 return wrap(base+wrap(target)-wrap(effective));
}
