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

// 938_Range_Sum_of_BST

// https://leetcode.com/problems/range-sum-of-bst/description/

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
    int rangeSumBST(TreeNode* root, int low, int high)
    {
        // TC ,
        // ([1], 0, 2)
        // ([1], 3, 4)
        // ([10], 3, 4)

        // return dst(root, low, high);
        return bst(root, low, high);
    }

private:
    int dst(TreeNode* node, int low, int high)
    {
        if (!node) return 0;

        int sum = 0;
        if (low <= node->val && node->val <= high)
        {
            sum = node->val;
        }

        if (low <= node->val) sum += dst(node->left, low, high);
        if (node->val <= high) sum += dst(node->right, low, high);

        return sum;
        // time: O(n)
        // space: O(H)
    }

    int bst(TreeNode* node, int low, int high)
    {
        int sum = 0;

        queue<TreeNode *> q;
        q.push(node);

        while(!q.empty())
        {
            node = q.front();
            q.pop();

            if (low <= node->val && node->val <= high)
            {
                sum += node->val;
            }

            if (node->left && low <= node->val) q.push(node->left);
            if (node->right && node->val <= high) q.push(node->right);
        }

        return sum;
    }
};
