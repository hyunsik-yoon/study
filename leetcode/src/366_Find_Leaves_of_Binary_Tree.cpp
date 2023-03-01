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

// 366_Find_Leaves_of_Binary_Tree

// https://leetcode.com/problems/find-leaves-of-binary-tree/description/

// 말단 노드들의 값들을 vector k 에 저장
// 그 위 노드들을 vector k-1 에 저장..
// 최종적으로 [vector_k, vector(k-1), .. vector_0] 를 리턴

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
    vector<vector<int>> findLeaves(TreeNode* root)
    {
        // return method_complex(root);
        return method_with_node_height(root);
    }

    vector<vector<int>> method_with_node_height(TreeNode* root)
    {
        // REMEMBER
        // node의 height는 말단 노드까지의 거리
        // 이 문제는 같은 height 인 애들을 모으면 되는 문제

        vector<vector<int>> v;

        process_with_height(root, v);
        return v;
    }

    int process_with_height(TreeNode *node, vector<vector<int>> &v)
    {
        // let's define height of initial terminal nodes is 0
        if (!node) return -1; // carefully check if this correct.

        int l_height = process_with_height(node->left, v);
        int r_height = process_with_height(node->right, v);

        int height = 1 + std::max(l_height, r_height);

        int v_idx = height;

        if (v_idx < v.size())
        {
            v[v_idx].emplace_back(node->val);
        }
        else
        {
            vector<int> vh{node->val};
            v.insert(v.begin() + v_idx, vh);
        }

        return height;
    }

    vector<vector<int>> method_complex(TreeNode* root)
    {
        // TC
        // [1]
        // [1, 2, 3, 4]

        // tree를 한번 traverse 하면서 leaf nodes 들을 모은다. 그 위 parent들은 leaf node를 가리키던 ptr를 nullptr로 만든다.
        // 복잡한 방식
        // 그리고 원래의 tree 구조도 바뀌게 된다.

        vector<vector<int>> ans;
        queue<TreeNode *> q;

        if (is_terminal(root))
            return {{root->val}};

        while (! is_terminal(root))
        {
            vector<int> vals;

            q.push(root);
            while (!q.empty())
            {
                auto *node = q.front();
                q.pop();

                if (node->left)
                {
                    if (is_terminal(node->left))
                    {
                        vals.emplace_back(node->left->val);
                        // TODO we need to delete node->left
                        node->left = nullptr;
                    }
                    else
                        q.push(node->left);
                }

                if (node->right)
                {
                    if (is_terminal(node->right))
                    {
                        vals.emplace_back(node->right->val);
                        // TODO we need to delete node->right
                        node->right = nullptr;
                    }
                    else
                        q.push(node->right);
                }
            }

            ans.emplace_back(vals);
        }

        // not root is terminal
        ans.emplace_back(vector<int>{root->val});

        return ans;
    }

private:
    bool is_terminal(TreeNode *node)
    {
        return node->left == nullptr && node->right == nullptr;
    }
};
