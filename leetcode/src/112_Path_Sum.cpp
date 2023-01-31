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

// 112_Path_Sum

// https://leetcode.com/problems/path-sum/solutions/

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
    bool hasPathSum(TreeNode* root, int targetSum)
    {
        // return hasPathSum_recursive(root, targetSum);
        return hasPathSum_iterative(root, targetSum);
    }

private:
    bool hasPathSum_recursive(TreeNode* root, int targetSum) {
        if (! root) return false;

        if (root->left && hasPathSum(root->left, targetSum - root->val)) return true;

        if (root->right && hasPathSum(root->right, targetSum - root->val)) return true;

        if (is_terminal(root) && root->val == targetSum)
            return true;

        return false;
    }

private:
    bool hasPathSum_iterative(TreeNode* root, int targetSum)
    {
        if (! root) return false;

        using TargetSum = int;

        // REMEMBER
        // when recursion stack needs more data (e.g., TargetSum) include that into stack.
        // (recursion 방식도 그렇게 동작하니까.)
        stack<pair<TreeNode*,TargetSum>> st;

        st.push({root, targetSum});

        while(!st.empty())
        {
            auto ctx = st.top();
            st.pop();

            TreeNode *node = ctx.first;
            int target = ctx.second;

            if (is_terminal(node) && node->val == target)
                return true;

            if (node->left) st.push({node->left, target - node->val});
            if (node->right) st.push({node->right, target - node->val});
        }

        return false;
    }

private:
    bool is_terminal(TreeNode *node)
    {
        assert(node);
        return node->left == nullptr && node->right == nullptr;
    }
};
