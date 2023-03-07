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


// 1650_Lowest_Common_Ancestor_of_a_Binary_Tree_III

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/description/

// Definition for a Node.
// class Node {
// public:
//     int val;
//     Node* left;
//     Node* right;
//     Node* parent;
// };

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q)
    {
        // return method_one_set(p, q);
        // return method_two_sets(p, q);
        return method_start_from_ther_others(p, q);
    }

private:
    Node* method_start_from_ther_others(Node* p, Node * q)
    {
        // p    -----o---    where o is LCA
        //        A    B
        // q       --o---
        //          C  B     where C is num of nodes before o, B is num of nodes after o`

        // after end of p, continue to q : A-->B-->C  --(1)
        // after end of q, continue to p : C-->B-->A  --(2)   where (2) == ()1)

        auto *p_node = p;
        auto *q_node = q;

        while (p_node != q_node)
        {
            if (p_node == nullptr)
                p_node = q;
            else
                p_node = p_node->parent;

            if (q_node == nullptr)
                q_node = p;
            else
                q_node = q_node->parent;
        }

        return p_node;
    }

    Node* method_one_set(Node* p, Node * q)
    {
        unordered_set<Node*> p_ancestors;

        for (auto *p_node = p; p_node != nullptr; p_node = p_node->parent)
            p_ancestors.insert(p_node);

        for (auto *q_node = q; q_node != nullptr; q_node = q_node->parent)
        {
            if (p_ancestors.count(q_node) > 0)
            {
                return q_node;
            }
        }

        throw runtime_error("wrong problem");
    }

    Node* method_two_sets(Node* p, Node * q)
    {
        unordered_set<Node*> p_ancestors;
        unordered_set<Node*> q_ancestors;

        auto *p_node = p;
        auto *q_node = q;

        while (p_node != nullptr || q_node != nullptr)
        {
            p_ancestors.insert(p_node);
            q_ancestors.insert(q_node);

            if (p_ancestors.count(q_node) > 0)
            {
                return q_node;
            }
            if (q_ancestors.count(p_node) > 0)
            {
                return p_node;
            }

            if (p_node) p_node = p_node->parent;
            if (q_node) q_node = q_node->parent;
        }

        throw runtime_error("wrong problem");
    }
};
