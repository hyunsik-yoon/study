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

// 35_Search_Insert_Position

// https://leetcode.com/problems/search-insert-position/description/

class Solution {
public:
    int searchInsert(vector<int>& nums, int target)
    {
        // return search_recursive(nums, target, 0, nums.size() - 1);
        return search_iterative(nums, target);
    }

private:
    int search_recursive(vector<int>& nums, int target, int begin, int end)
    {
        // TC
        // [1], 1 or 2
        // [1, 3], 0, 1, 2, 5
        // [1,3,5,6], 2
        // [1, 3, 5, 7, 9], 2

        if (begin >= end && target < nums[begin]) return begin;
        if (begin >= end && target > nums[begin]) return begin + 1;

        int mid = begin + (end - begin)/2;
        if (target == nums[mid]) return mid;
        if (target < nums[mid]) return search_recursive(nums, target, begin, mid -1);
        else return search_recursive(nums, target, mid +1, end);
    }

    int search_iterative(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target)
                return mid;
            else if (target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        }

        if (right == left && target <= nums[left]) return left;
        if (right == left && target > nums[left]) return left + 1;
        if (right < left && target <= nums[left]) return left;
        if (right < left && target > nums[left]) return left + 1;

        throw runtime_error("error");
    }
};
