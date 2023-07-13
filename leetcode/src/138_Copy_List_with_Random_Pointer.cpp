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

// 138_Copy_List_with_Random_Pointer

// https://leetcode.com/problems/copy-list-with-random-pointer/description/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head)
    {
        if (!head) return nullptr;

        Node *new_head = nullptr;
        map<Node*,Node*> m;

        // create a node if it's not in m
        for (Node* node = head; node; node = node->next)
        {
            Node* new_node = nullptr;
            Node* next_node = nullptr;
            Node* random_node = nullptr;

            auto found_node = m.find(node);
            if (found_node != m.end())
            {
                new_node = found_node->second;
            }
            else
            {
                new_node = new Node(node->val);
                m[node] = new_node;
            }

            if (! new_head) new_head = new_node;

            if (node->next)
            {
                auto found_node = m.find(node->next);
                if (found_node != m.end())
                {
                    next_node = found_node->second;
                }
                else
                {
                    next_node = new Node(node->next->val);
                    m[node->next] = next_node;
                }
                new_node->next = next_node;
            }

            if (node->random)
            {
                auto found_node = m.find(node->random);
                if (found_node != m.end())
                {
                    random_node = found_node->second;
                }
                else
                {
                    random_node = new Node(node->random->val);
                    m[node->random] = random_node;
                }
                new_node->random = random_node;
            }
        }

        return new_head;
    }
};
