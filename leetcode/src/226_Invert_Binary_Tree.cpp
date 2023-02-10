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

// 226_Invert_Binary_Tree

// https://leetcode.com/problems/invert-binary-tree/description/

// invert tree

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
    TreeNode* invertTree(TreeNode* root)
    {
        // tc
        // []
        // [1]
        // case where right is null
        // normal case in examples

        //return invert_1(root);
        return invert_2(root);
    }

private:
    TreeNode* invert_1(TreeNode* node)
    {
        // for a node,
        //  change left and right recursively
        //
        // time: O(n)
        // space: O(log n) in optimal case, O(n) in the worst case (skewed tree)

        if (!node) return nullptr;

        TreeNode *l = node->left;
        node->left = node->right;
        node->right = l;

        invert_1(node->left);
        invert_1(node->right);

        return node;
    }

    TreeNode* invert_2(TreeNode* root)
    {
        // time: O(n)
        // space: skewed O(1)
        // c      omplete tree: number of terminal O(2^(h-1)), which is actually O(n)

        if (! root) return nullptr;

        // BFS
        queue<TreeNode*>q;

        q.push(root);
        while (!q.empty())
        {
            auto *node = q.front();
            q.pop();

            TreeNode *l = node->left;
            node->left = node->right;
            node->right = l;

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return root;
    }
};
