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

// 108_Convert_Sorted_Array_to_Binary_Search_Tree

// https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/description/

// make an array of int in ascending order into height-balanced BST,
// where height-balanced BST is a binary tree in which the depth of the two subtrees of
// every node never differs by more than one.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums)
    {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }

    TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end)
    {
        if (start > end)
            return nullptr;

        if (start == end)
            return new TreeNode(nums[start]);

        int mid = (start + end) / 2;

        // pick nums[mid] as root
        TreeNode *root = new TreeNode(nums[mid]);

        root->left = sortedArrayToBST(nums, start, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, end);

        return root;
    }
};
