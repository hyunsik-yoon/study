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

// 912. Sort an Array
// https://leetcode.com/problems/sort-an-array/description/

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        return msort(nums, 0, nums.size() - 1);
    }

    vector<int> msort(vector<int>& nums, int l, int r) {

        if (r == l)
            return {nums[r]};

        int m = l + (r-l)/2;

        vector<int> lv = msort(nums, l, m);
        vector<int> rv = msort(nums, m + 1, r);

        // merge
        vector<int> ans(lv.size() + rv.size());

        int lk = 0, rk = 0, ansk = 0;
        while (lk < lv.size() && rk < rv.size())
        {
            if (lv[lk] <= rv[rk]) ans[ansk++] = lv[lk++];
            else ans[ansk++] = rv[rk++];
        }

        while (lk < lv.size()) ans[ansk++] = lv[lk++];
        while (rk < rv.size()) ans[ansk++] = rv[rk++];

        return ans;
    }
};

/*
1 2 4 6
3 4 5 7

1 2 2 4
4 5 6 7

*/
