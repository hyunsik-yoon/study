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

// 704_Binary_Search

// https://leetcode.com/problems/binary-search/description/

class Solution {
public:
    int search(vector<int>& nums, int target)
    {
        // TC
        // [0]
        // [0, 1]
        // [0, 1, 2]
        // [0, 1, 2, 3]

        // return search_recursive(nums, 0, nums.size() - 1, target);
        return search_iterative(nums, target);
    }

private:
    int search_iterative(vector<int>& nums, int target)
    {
        // REMEMBER
        // relatively easier to implement

        int left = 0;
        int right = nums.size() - 1;

        while (left < right)
        {
            int mid = (left + right) / 2;

            if (nums[mid] == target)
                return mid;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid - 1;
        }

        // when left == right
        return (nums[left] == target ? left : -1);
    }

private:
    int search_recursive(vector<int>& nums, int left, int right, int target)
    {
        if (left == right)
            return (nums[left] == target ? left : -1);

        if (left + 1 == right)
        {
            if (nums[left] == target) return left;
            else if (nums[right] == target) return right;
            else return -1;
        }

        // REMEMBER  do not make a silly mistake
        int mid = (right + left) / 2;

        if (nums[mid] == target) return mid;
        else if (nums[mid] < target) return search_recursive(nums, mid + 1, right, target);
        else return search_recursive(nums, left, mid - 1, target);
    }
};
