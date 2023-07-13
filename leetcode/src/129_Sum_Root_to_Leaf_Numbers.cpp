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

// 129_Sum_Root_to_Leaf_Numbers

// https://leetcode.com/problems/sum-root-to-leaf-numbers/description/

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
    int sumNumbers(TreeNode* root)
    {
        return dfs(root, 0);
    }

private:
    int dfs(TreeNode* node, int parent)
    {
        // node must not be nullptr
        assert(node);

        // when leaf
        if (!node->left && !node->right)
        {
            return parent + node->val;
        }

        parent = (parent + node->val) * 10;

        int child_sum = 0;
        if(node->left) child_sum = dfs(node->left, parent);
        if(node->right) child_sum += dfs(node->right, parent);

        return child_sum;
    }
};

/*
node    0
parent  0
sum     0
*/
