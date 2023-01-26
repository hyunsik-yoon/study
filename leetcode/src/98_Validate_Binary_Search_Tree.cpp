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

// 98_Validate_Binary_Search_Tree

// https://leetcode.com/problems/validate-binary-search-tree/description/

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
    bool isValidBST(TreeNode* root)
    {
#if 0
        /*
        REMEMBER

        풀다보니 range 방식으로 풀게 되었는데

        Since validate() gets range with inclusive upper and lower bounds
        we should know how to set the initial value.

        이 풀에는 억지로 long 으로 해서 최대 최소값의 -1, +1 을 해줬는데.....

        다른 방법은 bool validate(TreeNode* node, TreeNode* min_node, TreeNode* max_node) 처럼 하고
        nullptr을 가지면 무한대로 처리하는 방법이 있다.
        */
        min_val = - pow(2, 31) - 1;
        max_val = pow(2, 31) - 1 + 1;

        return validate_with_range(root, min_val, max_val);
#endif
        current_max_node = nullptr;
        return validate_with_inorder(root);
    }

private:
    long min_val, max_val;

    // check if nodes are in specific range (min_num, max_num) <- inclusive
    bool validate_with_range(TreeNode* node, long min_num, long max_num)
    {
        if (! node) return true;

        if (min_num < node->val && node->val < max_num)
        {
            if (! validate_with_range(node->left, min_num, node->val))
                return false;
            if (! validate_with_range(node->right, node-> val, max_num))
                return false;

            return true;
        }

        return false;
    }

    /*
    REMEMBER

    다른 풀이법은 inorder traversal 방식.

    inorder traversal을 하면서 정렬된 숫자를 얻게 된다는데 착안.
    current_max 를 유지하여 visiting node 보다 작은지를 본다.
    */
    TreeNode* current_max_node;
    bool validate_with_inorder(TreeNode* node)
    {
        if (!node) return true;

        if (node->left)
        {
            if (!validate_with_inorder(node->left)) return false;
        }

        if (current_max_node && current_max_node->val >= node->val) return false;
        current_max_node = node;

        if (node->right)
        {
            if (!validate_with_inorder(node->right)) return false;
        }

        return true;
    }
};
