#pragma once
#include <algorithm>
#include <array>
#include <cmath>

// One row describes the probabilities for the grain following that row.
struct MarkovMatrix {
    static constexpr int size = 9;
    std::array<float, size * size> values {};

    void sequential(int active = size) noexcept {
        active = std::clamp(active, 1, size);
        values.fill(0.0f);
        // Queue position 0 is newest: Played moves toward it and wraps.
        for (int row=0; row<size; ++row)
            values[row*size + (row < active ? (row == 0 ? active-1 : row-1) : row)] = 1.0f;
    }
    void random() noexcept { values.fill(1.0f / size); }

    // Restrict choices to occupied queue positions; a row with no available
    // weight falls back to the next occupied grain in played order.
    int chooseNext(int row, int active, float randomUnit) const noexcept {
        active = std::clamp(active, 1, size);
        row = std::clamp(row, 0, active - 1);
        randomUnit = std::isfinite(randomUnit) ? std::clamp(randomUnit, 0.0f, 0.99999994f) : 0.0f;
        float sum = 0.0f;
        for (int col = 0; col < active; ++col) {
            const float weight = values[row * size + col];
            if (std::isfinite(weight) && weight > 0) sum += weight;
        }
        if (!(sum > 0)) {
            // A forward step just beyond the occupied range wraps to zero.
            if (active < size && row == active-1 && values[row*size+active] > 0.0f) return 0;
            return row == 0 ? active - 1 : row - 1;
        }
        float draw = randomUnit * sum;
        int last = 0;
        for (int col = 0; col < active; ++col) {
            const float weight = values[row * size + col];
            if (!std::isfinite(weight) || weight <= 0) continue;
            last = col;
            if (draw < weight) return col;
            draw -= weight;
        }
        return last;
    }

    // The visible row mirrors the distribution actually used by chooseNext.
    std::array<float, size> effectiveRow(int row, int active) const noexcept {
        std::array<float, size> result {};
        active = std::clamp(active, 0, size);
        if (row < 0 || row >= active) return result;
        float sum = 0;
        for (int col=0; col<active; ++col) {
            const float w=values[row*size+col];
            if (std::isfinite(w) && w>0) { result[col]=w; sum+=w; }
        }
        if (sum > 0) for (float &w:result) w/=sum;
        else {
            const int next=(active<size && row==active-1 && values[row*size+active]>0) ? 0 : (row==0 ? active-1 : row-1);
            result[next]=1.0f;
        }
        return result;
    }
    void setEffectiveProbability(int row, int col, int active, float value) noexcept {
        active=std::clamp(active,0,size);
        if (row<0 || row>=active || col<0 || col>=active || !std::isfinite(value)) return;
        auto probabilities=effectiveRow(row,active);
        value=active==1 ? 1.0f : std::clamp(value,0.0f,1.0f);
        float other=0; for(int i=0;i<active;++i) if(i!=col) other+=probabilities[i];
        for(int i=0;i<size;++i) values[row*size+i]=i>=active ? 0.0f : (i==col ? value : (other>0 ? (1-value)*probabilities[i]/other : (1-value)/(active-1)));
    }

    // Presets are complete first-order transition matrices.
    void preset(int kind, int active = size) noexcept {
        active = std::clamp(active, 1, size);
        if (kind == 1) { sequential(active); return; }
        values.fill(0.0f);
        for (int row=0; row<size; ++row) {
            if (row >= active) { values[row*size+row] = 1.0f; continue; }
            float sum=0.0f;
            for (int col=0; col<active; ++col) {
                int forward=(col-row+active)%active;
                int distance=std::min(forward,active-forward);
                float w=0.0f;
                switch(kind) {
                case 2: w=1.0f; break;
                case 3: w=distance==1 ? 4.0f : 1.0f; break;
                case 4: w=distance==1 ? 5.0f : (distance==0 ? 1.0f : 2.0f); break;
                case 5: w=distance==0 ? 8.0f : (distance==1 ? 2.0f : 1.0f); break;
                case 6: w=distance==1 ? 1.0f : 0.0f; break;
                case 7: w=distance==0 ? 0.1f : (distance==1 ? 1.0f : 5.0f); break;
                case 8: w=(forward==0 || forward==active-1) ? 1.0f : 0.0f; break;
                case 9: w=forward==(active-2+active)%active ? 1.0f : 0.0f; break;
                case 10: w=forward==(1%active) ? 1.0f : 0.0f; break;
                case 11: w=forward==active-1 ? 5.0f : (forward==(active-2+active)%active ? 2.0f : 1.0f); break;
                default: w=1.0f; break;
                }
                values[row*size+col]=w; sum+=w;
            }
            if (!(sum>0.0f)) { values[row*size+row]=1.0f; continue; }
            for (int col=0; col<active; ++col) values[row*size+col]/=sum;
        }
    }

    void setProbability(int row, int column, float value) noexcept {
        if (row < 0 || row >= size || column < 0 || column >= size || !std::isfinite(value)) return;
        value = std::clamp(value, 0.0f, 1.0f);
        const int base = row * size;
        float otherSum = 0.0f;
        for (int i=0; i<size; ++i) if (i != column) otherSum += std::max(0.0f, values[base+i]);
        const float remaining = 1.0f - value;
        for (int i=0; i<size; ++i) if (i != column)
            values[base+i] = otherSum > 0.0f ? remaining * std::max(0.0f, values[base+i]) / otherSum : remaining / (size-1);
        values[base+column] = value;
    }
};
