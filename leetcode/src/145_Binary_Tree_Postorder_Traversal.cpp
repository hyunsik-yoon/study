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

// 145_Binary_Tree_Postorder_Traversal

// https://leetcode.com/problems/binary-tree-postorder-traversal/description/

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
    vector<int> postorderTraversal(TreeNode* root)
    {
        unordered_set<TreeNode *> done;

        vector<int> ans;
        stack<TreeNode*> st;

        if (! root) return {};

        st.push(root);
        if (root->right) st.push(root->right);
        if (root->left) st.push(root->left);

        while (!st.empty())
        {
            auto *node = st.top();

            if (!node->right && !node->left)
            {
                ans.emplace_back(node->val);
                done.emplace(node);
                st.pop();
                continue;
            }
            // child(ren) was already processed
            // anyone is processed means they are both processed
            if (done.count(node->right) > 0 || done.count(node->left) > 0)
            {
                ans.emplace_back(node->val);
                done.emplace(node);
                st.pop();
                // to keep done small as possible, max size of done seems 3
                done.erase(node->right);
                done.erase(node->left);
                continue;
            }

            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }

        return ans;
    }
};
