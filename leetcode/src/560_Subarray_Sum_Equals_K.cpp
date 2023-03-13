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

// 560_Subarray_Sum_Equals_K

// https://leetcode.com/problems/subarray-sum-equals-k/description/

class Solution {
public:
    int subarraySum(vector<int>& nums, int target)
    {
        /*
        [1], 1
        [1,1,1], 2
        [1,2,3], k = 3
        [1,2,3,1], k = 3
        [-1, -1, 1], k = 0
        */

        int count = 0;
        unordered_map<int, int> prev_sum;

        int sum = 0;
        for (int k = 0; k < nums.size(); k++)
        {
            sum += nums[k];

            // does any sum_t exhist where sum_k - k = sum_t ?
            int diff = sum - target;
            if (diff == 0) count++;

            auto found = prev_sum.find(diff);
            if (found != prev_sum.end())
            {
                count += found->second;
            }

            // store sum
            found = prev_sum.find(sum);
            if (found != prev_sum.end())
            {
                found->second++;
            }
            else
            {
                prev_sum[sum] = 1;
            }
        }

        return count;
    }
};
