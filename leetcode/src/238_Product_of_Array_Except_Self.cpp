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

// 238_Product_of_Array_Except_Self

// https://leetcode.com/problems/product-of-array-except-self/description/

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums)
    {
        // return get_answer_o_n(nums);
        return get_answer_o_1(nums);
    }

    // solution with O(n) storage
    vector<int> get_answer_o_n(vector<int>& nums)
    {
        // TC
        // [1, 2], [1, 2, 3, 4]
        vector<int> left(nums.size()), right(nums.size());

        // prepare left
        left[0] = nums[0];
        for (int i = 1; i < nums.size() - 1; i++)
            left[i] = nums[i] * left[i-1];

        // prepare right
        int last = nums.size() - 1;
        right[last] = nums[last];
        for (int i = last - 1; i > 0; i--)
            right[i] = nums[i] * right[i+1];

        // prepare answer
        vector<int> ans(nums.size());
        ans[0] = right[1];
        ans[last] = left[last - 1];
        for (int i = 1; i <= last - 1; i++)
            ans[i] = left[i-1] * right[i+1];

        return ans;
    }

    // solution with O(1) storage (except return vector)
    vector<int> get_answer_o_1(vector<int>& nums)
    {
        // TC
        // [3, 2], [4, 2, 3]
        vector<int> ans(nums.size());

        // prepare right
        int last = nums.size() - 1;
        ans[last] = nums[last];
        for (int i = last - 1; i > 0; i--)
            ans[i] = nums[i] * ans[i+1];

        // left production before nums[i]
        int left = 1;

        // prepare answer
        for (int i = 0; i < last; i++)
        {
            ans[i] = ans[i+1] * left;

            left = left * nums[i];
        }

        ans[last] = left;

        return ans;
    }

};
