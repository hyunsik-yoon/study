#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_set>
#include <vector>

using namespace std;

// 78. Subsets

// https://leetcode.com/problems/subsets/description/

// integer list (superset)를 주고, 그 integer들로 만들 수 있는 집합을 전부 리턴. (superset's subsets)

// Note: the count of possible subsets: pow(2, N) 인것을 알면 풀기 쉬울 수 있는 문제
// 방법 1. 만일 k부터의 subset이 sk 이면, k-1 부터의 subset은 [sk], [nums[k-1], sk] 가 됨.
// 방법 2. knuth 아저씨의 bitmask 방법
//        k를 0에서 pow(2, n) 까지 loop을 돌리면서, k 의 각 t번째 bit가 1이면 nums[t]를 include한다.

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        // return method_recur(nums);
        return method_bitmask(nums);
    }

private:
    vector<vector<int>> method_bitmask(vector<int>& nums)
    {
        vector<vector<int>> ans(pow(2, nums.size()), std::move(vector<int>()));

        for (uint32_t k = 0; k < pow(2, nums.size()); ++k)
        {
            auto &v = ans[k];

            uint32_t bits = k;
            uint32_t mask = 1;
            for (int t = 0; t < nums.size(); ++t)
            {
                if (bits & mask) v.emplace_back(nums[t]);
                mask = mask << 1;
            }
        }

        return ans;
    }


    vector<vector<int>> method_recur(vector<int>& nums)
    {
        return get_subset(nums, 0);
    }

    vector<vector<int>> get_subset(vector<int>& nums, int start)
    {
        if (start == nums.size() -1)
        {
             auto ans = vector<vector<int>>();
             ans.emplace_back(vector<int>());
             ans.emplace_back(vector<int>{nums[start]});

             return ans;
        }
        else
        {
            auto ans = get_subset(nums, start + 1);

            vector<vector<int>> ans2{ans};
            std::for_each(ans2.begin(), ans2.end(), [&nums, start](vector<int> &v) { v.emplace_back(nums[start]); });

            int N = ans.size();
            ans.resize(2*N);

            for (int k = 0; k < ans2.size(); k++)
                swap(ans2[k], ans[N+k]);

            return ans;
        }
    }
};

/* TC
[10], {{10}, {}}
[5, 10]    {{10}, {}, {10, 5}, {5}}   {{10, 5}, {5}}
[0, 1, 2]

start = 2


*/
