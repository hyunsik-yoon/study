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


// 250_Count_Univalue_Subtrees

// https://leetcode.com/problems/count-univalue-subtrees/description/

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
    int countUnivalSubtrees(TreeNode* root)
    {
        if (! root) return 0;

        int val = 0;
        find_unival_subtree(root, val);

        return val;
    }

    bool find_unival_subtree(TreeNode *root, int& count)
    {
        assert(root);

        if (!root->left && !root->right)
        {
            count++;
            return true;
        }

        bool left_found = root->left && find_unival_subtree(root->left, count);
        bool right_found = root->right && find_unival_subtree(root->right, count);

        bool i_am_unival =
            (root->left == nullptr && right_found && root->val == root->right->val) ||
            (root->right == nullptr && left_found && root->val == root->left->val) ||
            (left_found && right_found && root->val == root->right->val && root->val == root->left->val);

        if (i_am_unival)
        {
            count++;
            return true;
        }

        return false;
    }
};
