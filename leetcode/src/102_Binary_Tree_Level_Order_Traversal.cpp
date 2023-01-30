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

// 102_Binary_Tree_Level_Order_Traversal

// https://leetcode.com/problems/binary-tree-level-order-traversal/description/

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
    vector<vector<int>> levelOrder(TreeNode* root)
    {
        // return levelOrder_n_2n(root);
        return levelOrder_n_n(root);
    }

    vector<vector<int>> levelOrder_n_n(TreeNode* root)
    {
        vector<vector<int>> ans;
        deque<TreeNode*> dq;

        if (! root) return {};

        dq.emplace_back(root);

        int level = 0;
        while (!dq.empty())
        {
            auto level_count = dq.size();

            ans.emplace_back(vector<int>{});
            auto &v = ans[level];

            // REMEMBER number in queue is level_conut in BFS
            for (int k = 0; k < level_count; k++)
            {
                auto *node = dq.front();
                dq.pop_front();

                v.emplace_back(node->val);

                if (node->left) dq.emplace_back(node->left);
                if (node->right) dq.emplace_back(node->right);

            }

            level++;
        }

        return ans;
    }

    vector<vector<int>> levelOrder_n_2n(TreeNode* root)
    {
        vector<vector<int>> ans;
        deque<NodeCtx> dq;

        if (! root) return {};

        dq.emplace_back(NodeCtx{root, 0});

        while (!dq.empty())
        {
            // REMEMBER
            // 처음엔 auto &ctx = dq.front(); 로 reference로 했더니 자꾸 죽는다.
            // 이게 다음줄에서 dq.pop_front() 하면서 dq.empty()가 되면 레퍼런스된 메모리가 invalidate 해지는 것 같다.
            auto ctx = dq.front();
            dq.pop_front();

            if (ans.size() == ctx.level)
            {
                ans.emplace_back(vector<int>{ctx.node->val});
            }
            else
            {
                auto &v = ans[ctx.level];
                v.emplace_back(ctx.node->val);
            }

            if (ctx.node->left) dq.emplace_back(NodeCtx{ctx.node->left, ctx.level + 1});
            if (ctx.node->right) dq.emplace_back(NodeCtx{ctx.node->right, ctx.level + 1});
        }

        return ans;
    }
private:
    struct NodeCtx
    {
        TreeNode* node;
        int level;
    };
};
