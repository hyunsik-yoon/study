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

// 228_Summary_Ranges

// https://leetcode.com/problems/summary-ranges/description/

class Solution {
public:
    vector<string> summaryRanges(vector<int>& nums)
    {
        if (nums.size() == 0) return {};
        if (nums.size() == 1) return {to_string(nums[0])};

        vector<string> ans;
        auto append_ans = [&nums, &ans](int start, int end) {
            if (start == end) ans.push_back(to_string(nums[start]));
            else ans.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
        };

        int start = 0;

        for (auto k = 1; k < nums.size(); k++)
        {
            if (nums[k-1] + 1 < nums[k])
            {
                append_ans(start, k - 1);
                start = k;
            }
        }

        append_ans(start, nums.size() - 1);
        return ans;
    }
};

/* tc: [0], [0, 2], [0, 1, 2, 3]
*/
