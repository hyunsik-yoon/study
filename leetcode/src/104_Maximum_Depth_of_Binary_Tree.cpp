#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 104_Maximum_Depth_of_Binary_Tree

// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/

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
    int maxDepth(TreeNode* root)
    {
        // return maxDepth_recursive(root);
        return maxDepth_iteration(root);
    }

    int maxDepth_recursive(TreeNode* root)
    {
        if (! root)
        {
            return 0;
        }
        else
        {
            return 1 + max(maxDepth_recursive(root->left), maxDepth_recursive(root->right));
        }
    }

    int maxDepth_iteration(TreeNode* root)
    {
        if (! root)
            return 0;

        int max_depth = 0;

        stack<pair<TreeNode*, int>> stack;
        stack.push({root, 1});

        for (; not stack.empty(); )
        {
            auto node_ctx = stack.top();
            stack.pop();

            auto *node = node_ctx.first;
            auto depth = node_ctx.second;

            // REMEMBER
            max_depth = max(depth, max_depth);

            if (node->left) stack.push({node->left, depth+1});
            if (node->right) stack.push({node->right, depth+1});
        }

        return max_depth;
    }
};
