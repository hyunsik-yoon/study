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

// 1470_Shuffle_the_Array
// https://leetcode.com/problems/shuffle-the-array/description/

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        vector<int> ans(2*n);

        int t1 = 0, t2 = n;

        for (int k = 0; k < n; ++k, ++t1, ++t2)
        {
            ans[2*k] = nums[t1];
            ans[2*k + 1] = nums[t2];
        }

        return ans;
    }
};
