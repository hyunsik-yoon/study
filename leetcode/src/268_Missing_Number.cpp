#include <algorithm>
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

// 268_ Missing_Number

// https://leetcode.com/problems/missing-number/description/

// 어떤 수 n 에 대해, size n 어레이가 주어지고 그 안에 0 ~ n 까지의 distinct 수 중 하나를 뺀 수들이 들어 있다.
// 빠진 수를 찾아라.

class Solution {
public:
    int missingNumber(vector<int>& nums)
    {
        // return solve_gaus(nums);
        // return solve_sort(nums);
        return solve_map(nums);
    }

    int solve_map(vector<int>& nums)
    {
        unordered_set<int> set;

        for (auto num: nums)
            set.emplace(num);

        for (int i = 0; i <= nums.size(); i++)
        {
            if (set.count(i) == 0)
                return i;
        }

        throw std::runtime_error("Should not be here");
    }

    int solve_sort(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != i)
                return i;
        }

        return nums.size();
    }

    int solve_gaus(vector<int>& nums)
    {
        int n = nums.size();

        int total_sum = n * (n + 1) / 2;

        for (auto num : nums)
        {
            total_sum -= num;
        }

        return total_sum;
    }
};
