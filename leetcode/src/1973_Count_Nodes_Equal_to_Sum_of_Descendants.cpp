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

// 1973_Count_Nodes_Equal_to_Sum_of_Descendants

// https://leetcode.com/problems/count-nodes-equal-to-sum-of-descendants/description/
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
    int equalToDescendants(TreeNode* root) {
        int count = 0;
        traverse(root, count);
        return count;
    }

private:
    unsigned long traverse(TreeNode* node, int &count)  // return sum of tree including node
    {
        auto unsigned long sum = 0;
        if (node->left) sum = traverse(node->left, count);
        if (node->right) sum += traverse(node->right, count);

        if (sum == node->val) ++count;

        return node->val + sum;
    }
};
/*
[1]
count 0
sum 0

[3, 2, 1]
count 1
sum 3
*/
