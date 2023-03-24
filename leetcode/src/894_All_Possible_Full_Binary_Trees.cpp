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

// 894_All_Possible_Full_Binary_Trees

// https://leetcode.com/problems/all-possible-full-binary-trees/description/

// n 개의 node로 만들 수 있는 모든 full binary tree 의 root 를 리턴하라. full binary tree 란, 모든 node가 0개 또는 2개의 노드를 가지는 트리.

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
    vector<TreeNode*> allPossibleFBT(int n) {

        if (n % 2 == 0) return {};

        return gen(n);
    }

private:
    vector<TreeNode*> gen(int n)
    {
        map<int, vector<TreeNode *>> m;

        m[1] = vector<TreeNode*>{new TreeNode()};

        for (int x = 3; x <= n; x += 2)
        {
            vector<TreeNode *> v;
            int lc = 1;
            while (true)
            {
                int rc = x - 1 - lc;
                if (rc < 0) break;

                vector<TreeNode *> left_candidates = m[lc];
                vector<TreeNode *> right_candidates = m[rc];

                for (auto *l_root: left_candidates)
                {
                    for (auto *r_root: right_candidates)
                    {
                        v.push_back(new TreeNode(0, l_root, r_root));
                    }
                }

                lc += 2;
            }
            m[x] = v;
        }

        return m[n];
    }
};
