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

// 53. Maximum Subarray
// https://leetcode.com/problems/maximum-subarray/

class Solution {
public:
    int maxSubArray(vector<int>& nums) {

        if (nums.size() == 1) return nums[0];

        int min_pk = 0;
        int sum_k = 0;
        int max_k = std::numeric_limits<int>::min();

        for (int k = 0; k < nums.size(); ++k)
        {
            sum_k += nums[k];

            if (sum_k - min_pk > max_k)
                max_k = sum_k - min_pk;

            if (min_pk > sum_k)
                min_pk = sum_k;
        }

        return max_k;
    }
};
/*

-2, 1


k   min sum max
0   0   -2  -2
1       -1


-2, 1,-3,4,-1,2,1,-5,4
-2 -1 -4 0 -1 1 2 -3 1

-2 -1
-2 -3

*/
