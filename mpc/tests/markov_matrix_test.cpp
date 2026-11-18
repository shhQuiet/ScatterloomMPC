#include "../src/MarkovMatrix.h"
#include <cassert>
#include <cmath>

static bool close(float a, float b) { return std::abs(a-b) < 0.00001f; }
int main() {
    MarkovMatrix m; m.random();
    m.setProbability(2, 3, 0.5f);
    float sum=0;
    for(int i=0; i<9; ++i) { sum+=m.values[18+i]; if(i!=3) assert(close(m.values[18+i], 0.0625f)); }
    assert(close(sum, 1.0f));
    assert(close(m.values[0], 1.0f/9));
    m.setProbability(2, 3, 1.0f);
    m.setProbability(2, 3, 0.2f);
    for(int i=0; i<9; ++i) if(i!=3) assert(close(m.values[18+i], 0.1f));
    auto before=m.values; m.setProbability(-1, 0, 0.5f); assert(m.values == before);
    m.random();
    assert(m.chooseNext(0, 3, 0.0f) == 0);
    assert(m.chooseNext(0, 3, 0.5f) == 1);
    assert(m.chooseNext(0, 3, 0.999f) == 2);
    m.values.fill(0.0f);
    m.values[8] = 1.0f; // Grain nine is unavailable.
    assert(m.chooseNext(0, 3, 0.8f) == 2);
    m.values[1] = 1.0f;
    assert(m.chooseNext(0, 3, 0.99f) == 1);
    for (int preset=1; preset<=11; ++preset) {
        m.preset(preset);
        for (int row=0; row<9; ++row) {
            float total=0.0f;
            for (int col=0; col<9; ++col) { auto w=m.values[row*9+col]; assert(w>=0.0f && w<=1.0f); total+=w; }
            assert(close(total,1.0f));
        }
    }
    for (int count=1; count<=9; ++count) for (int preset=1; preset<=11; ++preset) {
        m.preset(preset,count);
        for (int row=0; row<count; ++row) {
            float total=0;
            for (int col=0; col<9; ++col) {
                const auto weight=m.values[row*9+col];
                if(col>=count) assert(close(weight,0.0f));
                total+=weight;
            }
            assert(close(total,1.0f));
            if (preset==1) assert(m.chooseNext(row,count,0.5f)==(row==0?count-1:row-1));
            if (preset==10) assert(m.chooseNext(row,count,0.5f)==(row+1)%count);
        }
    }
    m.preset(10);
    for (int count : {1, 3, 9}) for (int row=0; row<count; ++row)
        assert(m.chooseNext(row,count,0.5f)==(row+1)%count);
    m.sequential();
    assert(m.values[8] == 1.0f && m.values[9] == 1.0f);
    m.sequential(3);
    assert(m.values[2] == 1.0f && m.values[9] == 1.0f && m.values[19] == 1.0f);
}
