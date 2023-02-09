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

// 100_Same_Tree

// https://leetcode.com/problems/same-tree/description/

// 두 tree 가 same 인가?
// 모든 노드에 대해 val이 같고, left 와 right 가 같으면 same

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
    bool isSameTree(TreeNode* p, TreeNode* q)
    {
        //return isSameTree_recursive(p, q);
        return isSameTree_iterative(p, q);
    }

private:

    bool isSameTree_recursive(TreeNode* p, TreeNode* q)
    {
        if (is_same_node(p, q) == false) return false;

        if (p && isSameTree_recursive(p->left, q->left) == false) return false;

        if (p && isSameTree_recursive(p->right, q->right) == false) return false;

        return true;
    }

    bool is_same_node(TreeNode* p, TreeNode* q)
    {
        if (p == nullptr && q == nullptr) return true;

        if ((p == nullptr && q != nullptr) || (p != nullptr && q == nullptr)) return false;

        if (p->val != q->val) return false;

        return true;
    }

    bool isSameTree_iterative(TreeNode* p, TreeNode* q)
    {
        queue<TreeNode *> pq;
        queue<TreeNode *> qq;

        pq.push(p);
        qq.push(q);

        while (!(pq.empty() || qq.empty()))
        {
            auto *p_node = pq.front();
            auto *q_node = qq.front();

            pq.pop();
            qq.pop();

            if (!p_node && !q_node)
                continue;
            if ((p_node && !q_node) || (!p_node && q_node)) return false;

            if (p_node->val != q_node->val) return false;

            pq.push(p_node->left);
            qq.push(q_node->left);

            pq.push(p_node->right);
            qq.push(q_node->right);
        }

        if (!(pq.empty() && qq.empty())) return false;

        return true;
    }
};
