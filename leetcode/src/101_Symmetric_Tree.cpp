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

// 101_Symmetric_Tree

// https://leetcode.com/problems/symmetric-tree/description/
// 트리의 좌우가 거울 반사형인가

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
    bool isSymmetric(TreeNode* root)
    {
        // return isSymmetric_recursive(root);
        return isSymmetric_iterative(root);
    }

private:
    bool isSymmetric_iterative(TreeNode* root)
    {
        if (!root) return true;

        // use lq, rq
        deque<TreeNode *> lq, rq;

        lq.emplace_back(root->left);
        rq.emplace_back(root->right);

        while (!lq.empty() && !rq.empty())
        {
            if (lq.size() != rq.size())
                return false;

            auto *l_node = lq.front();
            lq.pop_front();

            auto *r_node = rq.front();
            rq.pop_front();

            if (!l_node && !r_node) continue;
            if (l_node && r_node)
            {
                if (l_node->val != r_node->val) return false;

                lq.emplace_back(l_node->left);
                lq.emplace_back(l_node->right);

                // REMEMBER
                // reverse storing
                rq.emplace_back(r_node->right);
                rq.emplace_back(r_node->left);
            }
            else return false;
        }
        return true;
    }

private:
    bool isSymmetric_recursive(TreeNode* root)
    {
        if (!root)
            return true;

        return is_mirror(root->left, root->right);
    }

    bool is_mirror(TreeNode* left, TreeNode* right)
    {
        if (!left && !right)
            return true;

        if (left && right)
        {
            return (left->val == right->val) &&
                   is_mirror(left->left, right->right) &&
                   is_mirror(left->right, right->left);
        }

        return false;
    }
};
