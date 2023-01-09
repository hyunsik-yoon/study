#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 700_Search_in_a_Binary_Search_Tree

// https://leetcode.com/problems/search-in-a-binary-search-tree/description/

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
    TreeNode* searchBST(TreeNode* root, int val) {
        // return searchBST_recursive(root, val);
        return searchBST_iterative(root, val);
    }

    TreeNode* searchBST_recursive(TreeNode* root, int val)
    {
        if (not root)
            return root; // []
        if (val == root->val)
            return root;
        else if (val < root->val)
            return searchBST_recursive(root->left, val);
        else // (val > root->val)
            return searchBST_recursive(root->right, val);
    }

    TreeNode* searchBST_iterative(TreeNode* root, int val)
    {
        while (root)
        {
            if (val == root->val)
                return root;
            else if (val < root->val)
                root = root->left;
            else // (val > root->val)
                root = root->right;
        }

        return nullptr;
    }
};
