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

// 270_Closest_Binary_Search_Tree_Value
//
// https://leetcode.com/problems/closest-binary-search-tree-value/description/

/*
given variable target,

in binary search tree
    find a node with smallest abs(node->val - target)
*/

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

struct MinCtx
{
    TreeNode* node;
    double diff;
};

class Solution {
public:
    int closestValue(TreeNode* node, double target)
    {
        // find the terminal node to put the target
        // while keeping [val, min diff] value

        MinCtx min_ctx{nullptr, 1000000000};

        while (node)
        {
            double diff = abs(target - node->val);

            if (diff == 0) return node->val;

            if (diff < min_ctx.diff)
            {
                min_ctx.node = node;
                min_ctx.diff = diff;
            }

            if (node->val < target)
                node = node->right;
            else if (target < node->val)
                node = node->left;
        }

        return min_ctx.node->val;
    }
};
