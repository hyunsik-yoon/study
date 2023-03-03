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


// 314_Binary_Tree_Vertical_Order_Traversal

// https://leetcode.com/problems/binary-tree-vertical-order-traversal/description/

// tree 를 컬럼별로 정리해서 보여주는 문제
// root 가 column 0, root->left 가 comumn -1, root->left->left 는 colmumn -2, root->left->right 는 colmumn 0
// 이런식


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
    vector<vector<int>> verticalOrder(TreeNode* root)
    {
        return method_map(root);
    }

private:
    using Column = int;

    vector<vector<int>> method_map(TreeNode* root)
    {
        if (!root) return {};

        map<int, vector<int>> m; // ordered
        vector<vector<int>> res;

        // populate map
        bfs(root, m); // O(n log(n))

        // build res from map
        for (const pair<int, vector<int>> &pr: m)   // O(n)
            res.emplace_back(pr.second);

        return res;
    }

    void bfs(TreeNode* root, map<int, vector<int>> &m)
    {
        queue<pair<Column, TreeNode*>> q;

        q.push(pair{0, root});

        while (!q.empty())
        {
            // REMEMBER
            //  처음에 auto &pr = q.front() 라고 했는데 run 결과 메모리 에러 발생
            //  왜? 왜냐면 reference pr 이 q.pop() 하면서 더이상 유효하지 않아졌기 때문.....
            auto pr = q.front();
            q.pop();

            int col = pr.first;
            auto* node = pr.second;

            auto found = m.find(col);
            if (found != m.end())
                found->second.emplace_back(node->val);
            else
                m[col] = {node->val};

            // handle children
            if (node->left) q.push(pair{col - 1, node->left});
            if (node->right) q.push(pair{col + 1, node->right});
        }
    }
};
