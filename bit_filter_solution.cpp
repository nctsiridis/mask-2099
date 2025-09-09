#include <vector>
#include <cstdint>
using namespace std;

typedef uint32_t u32;

class BitFilterSolution {
public:
    int N;

    int topKStat(const vector<int>& nums, vector<int>& stat, const bool neg, int k) {
        vector<int> ones, zeros;
        for (int i = 0; i < 32; ++i) {
            u32 mask = 1u << (31 - i);
            ones.clear();
            zeros.clear();
            int c = 0;
            for (int j = 0; j < N; ++j) {
                int raw = nums[j];
                if (!neg && raw <= 0 || neg && raw > 0 || stat[j] < 2) continue;
                u32 x = neg ? (u32)(~(-raw)) : (u32)raw;
                if (x & mask) {
                    ++c;
                    ones.push_back(j);
                } else {
                    zeros.push_back(j);
                }
            }
            if (c > k) {
                for (int idx : zeros) stat[idx] = 0;
            } else {
                for (int idx : ones) stat[idx] = 1;
                k -= c;
            }
            if (k == 0) break;
        }
        for (int i = 0; i < N && k > 0; ++i) {
            if (stat[i] == 2 && ((!neg && nums[i] > 0) || (neg && nums[i] <= 0))) {
                stat[i] = 1;
                --k;
            }
        }
        return k;
    }

    vector<int> maxSubsequence(vector<int>& nums, int k) {
        N = nums.size();
        vector<int> stat(N, 2);
        int rem = topKStat(nums, stat, false, k);
        if (rem > 0) topKStat(nums, stat, true, rem);
        vector<int> res;
        res.reserve(k);
        for (int i = 0; i < N; ++i) {
            if (stat[i] == 1)
                res.push_back(nums[i]);
        }
        return res;
    }
};
