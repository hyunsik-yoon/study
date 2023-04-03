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

// 1382_Balance_a_Binary_Search_Tree

// https://leetcode.com/problems/balance-a-binary-search-tree/description/

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
    TreeNode* balanceBST(TreeNode* root)
    {
        return method1(root);
    }

    TreeNode* method1(TreeNode* root)
    {
        if (!root->left && !root->right) return root;

        vector<int> v;

        traverse_inorder(root, v);

        return build_balanceBST(v, 0, v.size() - 1);
    }

    void traverse_inorder(TreeNode* root, vector<int>& v)
    {
        if (! root) return;

        if (root->left) traverse_inorder(root->left, v);
        v.emplace_back(root->val);
        if (root->right) traverse_inorder(root->right, v);
    }

    TreeNode* build_balanceBST(const vector<int> &v, int start, int end)
    {
        if (start > end) return nullptr;

        // REMEMBER
        //      아래 경우를 한번 더 recursive하게 돌려보면 위의 베이스 케이스가 된다.
        // if (start == end) return new TreeNode(v[start], nullptr, nullptr);

        int mid = start + (end - start) / 2;
        auto *root = new TreeNode(v[mid]);

        auto *l_tree = build_balanceBST(v, start, mid - 1);
        auto *r_tree = build_balanceBST(v, mid + 1, end);

        root->left = l_tree;
        root->right = r_tree;

        return root;
    }
};
/*
1 2 3 4
    s e
    2 3

m = 2


*/
