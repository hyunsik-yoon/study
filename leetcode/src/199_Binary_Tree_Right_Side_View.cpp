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

// 199_Binary_Tree_Right_Side_View
// https://leetcode.com/problems/binary-tree-right-side-view/description/
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
    vector<int> rightSideView(TreeNode* root)
    {
        if (!root) return {};

        vector<int> ans;
        int visited = -1; // k if we push node->val into ans and the biggest depth of node is k
        dfs(root, 0, ans, visited);

        return ans;
    }

private:
    // traversing order : node -> right -> left
    void dfs(TreeNode* node, int depth, vector<int> &ans, int &visited)
    {
        if (depth > visited)
        {
            ans.push_back(node->val);
            visited = depth;
        }

        if (node->right) dfs(node->right, depth+1, ans, visited);
        if (node->left) dfs(node->left, depth+1, ans, visited);
    }
};
/* TC
[]
[1]

ans [1, 3]
visited [0, 1]
*/
