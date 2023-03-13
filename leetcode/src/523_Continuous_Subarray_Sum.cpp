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

// 523_Continuous_Subarray_Sum

// https://leetcode.com/problems/continuous-subarray-sum/description/

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int target)
    {
        /* TC
        [0], 1
        [18], 3
        [23,6], k = 6
        [23,2,4,6,7], k = 6
        [2, 4, 3], k = 6
        [1, 2, 3], k = 5
        */
        unordered_map<int /* reminder */, int /* smallest index */> m;

        int sum = 0;
        for (int k = 0; k < nums.size(); k++)
        {
            sum += nums[k];

            int reminder = sum % target;
            if (reminder == 0 && k >= 1) return true;

            auto found = m.find(reminder);
            if (found != m.end()) // found
            {
                if (k - found->second >= 2) return true;
            }
            else
                m[reminder] = k;
        }

        return false;
    }
};

/*
REMEMBER

for t < k
n*target = sum[k] - sum[t]

(sum[k] - sum[t]) % target == 0

    i.e.,
     ------t----------k----
           .   7      .
           13         20
      7 -> +6   14 -> +6
     k*1        k*2

    so, sum[t] % target == sum[k] % target
*/
