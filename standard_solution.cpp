#include <vector>
#include <algorithm>
using namespace std;

class StandardSolution {
public:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<pair<int, int>> with_index;
        for (int i = 0; i < nums.size(); ++i)
            with_index.emplace_back(nums[i], i);

        nth_element(with_index.begin(), with_index.begin() + k, with_index.end(),
                    [](const auto& a, const auto& b) {
                        return a.first > b.first;
                    });

        vector<pair<int, int>> top_k(with_index.begin(), with_index.begin() + k);
        sort(top_k.begin(), top_k.end(), [](auto& a, auto& b) { return a.second < b.second; });

        vector<int> res;
        res.reserve(k);
        for (auto& p : top_k)
            res.push_back(p.first);
        return res;
    }
};
