#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 219_Contains_Duplicate_II
//
// https://leetcode.com/problems/contains-duplicate-ii/description/

// REMEMBER
//     technique: window sliding
//     1. nested loop: inner loop scans elements in window
//     2. loop and BST: inside loop, call BST.contain          , where search takes O(logN)
//     3. loop and set: inside loop, call set.contain          , where search takes O(1)

// REMEMBER

// REMEMBER
//      it seems that C++ std lib does not implement BST. set or map instead.
//         -> https://stackoverflow.com/questions/5085091/binary-search-tree-implementation-in-c-stl
//
//      C++ set and map are usually implemented using a red–black tree,
//      which is a kind of self-balancing binary search tree.

class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k)
    {
        // return second_impl(nums, k);
        return third_impl(nums, k);
    }

    bool second_impl(vector<int>& nums, int distance)
    {
        // initial idea is to create window first

        // REMEMBER
        // Beware of the size of window. What happen if window is 0 or too large?

        if (distance == 0) return false;
        if (distance > nums.size()) distance = nums.size();

        // the idea is to

        // create a set that contains before index n by distance
        unordered_set<int> before;
        for (int k = 0; k < distance; k++)
        {
            if (before.count(nums[k]) > 0) return true;
            else before.emplace(nums[k]);
        }

        // loop
        for (int k = distance; k < nums.size(); k++)
        {
            if (before.count(nums[k]) > 0) return true;
            else {
                before.erase(nums[k - distance]);
                before.emplace(nums[k]);
            }
        }

        return false;
    }

    // based on official solution
    bool third_impl(vector<int>& nums, int distance)
    {
        if (distance == 0) return false;
        if (distance > nums.size()) distance = nums.size();

        unordered_set<int> before;
        for (int k = 0; k < nums.size(); k++)
        {
            if (before.count(nums[k]) > 0) return true;

            // REMEMBER: Window is maintained inside loop
            if (before.size() >= distance)
                before.erase(nums[k - distance]);
            before.emplace(nums[k]);
        }

        return false;
    }
};
