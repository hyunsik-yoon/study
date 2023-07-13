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

// 515_Find_Largest_Value_in_Each_Tree_Row
// https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/

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
    vector<int> largestValues(TreeNode* root) {

        if (! root) return {};

        queue<pair<TreeNode*, int>> q;
        vector<int> ans;

        q.push(make_pair(root, 0));

        while(!q.empty())
        {
            auto node_info = q.front();
            q.pop();

            int node_depth = node_info.second;

            // there's already some number for this depth
            if (ans.size() == node_depth + 1)
            {
                int &current_max = *ans.rbegin();
                if (current_max < node_info.first->val)
                    current_max = node_info.first->val;
            }
            else ans.push_back(node_info.first->val);

            int next_depth = node_info.second + 1;
            if (node_info.first->left) q.push(make_pair(node_info.first->left, next_depth));
            if (node_info.first->right) q.push(make_pair(node_info.first->right, next_depth));
        }

        return ans;
    }
};
