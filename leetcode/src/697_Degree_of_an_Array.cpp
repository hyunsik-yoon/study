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

// 697_Degree_of_an_Array
// https://leetcode.com/problems/degree-of-an-array/description/

class Solution {
public:
    int findShortestSubArray(vector<int>& nums)
    {
        struct NumCtx {
            int occurences;
            int k1, k2;
        };

        int degree = 1;
        unordered_map<int, NumCtx> num_map;

        for (int k = 0; k < nums.size(); ++k)
        {
            auto found = num_map.find(nums[k]);

            if (found != num_map.end())
            {
                NumCtx &ctx = found->second;
                ctx.occurences++;
                ctx.k2 = k;

                degree = max(degree, ctx.occurences);
            }
            else
            {
                num_map[nums[k]] = {1, k, -1};
            }
        }

        if (degree == 1) return 1;

        int len = 500001;
        for (auto p: num_map)
        {
            NumCtx &ctx = p.second;
            if (ctx.occurences == degree)
                len = std::min(ctx.k2 - ctx.k1 + 1, len);
        }

        return len;
    }
};
