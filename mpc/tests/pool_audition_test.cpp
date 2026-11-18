#include "../src/PoolAudition.h"
#include <cassert>
#include <cmath>
int main() {
 ScatterloomStatusBridge pool;
 pool.queue[0]=2; pool.queue[1]=4;
 pool.audioLeft[2]={.1f,.2f,.3f}; pool.audioRight[2]={.3f,.2f,.1f}; pool.valid[2]=3;pool.complete[2]=true;
 pool.audioLeft[4]={.4f,.4f,.4f}; pool.audioRight[4]={.2f,.2f,.2f}; pool.valid[4]=3;pool.complete[4]=true;
 PoolAudition p;
 assert(!p.trigger(pool,2,200));
 assert(p.trigger(pool,0,200));
 auto a=p.next(pool);assert(std::abs(a[0]-.1f)<1e-6f && std::abs(a[1]-.3f)<1e-6f);
 assert(p.trigger(pool,1,200));
 auto b=p.next(pool);assert(std::abs(b[0]-.6f)<1e-6f && std::abs(b[1]-.4f)<1e-6f);
 p.next(pool);p.next(pool);auto c=p.next(pool);assert(c[0]==0 && c[1]==0);
 assert(p.trigger(pool,0,200));pool.complete[2]=false;auto d=p.next(pool);assert(d[0]==0 && d[1]==0);
}
