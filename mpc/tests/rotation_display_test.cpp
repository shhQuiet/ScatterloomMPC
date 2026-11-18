#include "../src/RotationMath.h"
#include <cassert>
int main() {
 for(int steps=1;steps<=32;++steps)
  for(int base=0;base<steps;++base)
   for(int offset=0;offset<steps;++offset)
    for(int target=0;target<steps;++target) {
     int effective=(base+offset)%steps;
     int adjusted=scatterloomRotationBaseForTarget(base,effective,target,steps);
     assert((adjusted+offset)%steps==target);
    }
}
