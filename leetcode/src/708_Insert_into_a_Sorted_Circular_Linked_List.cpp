#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 708_Insert_into_a_Sorted_Circular_Linked_List

// https://leetcode.com/problems/insert-into-a-sorted-circular-linked-list/description/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;

    Node() {}

    Node(int _val) {
        val = _val;
        next = NULL;
    }

    Node(int _val, Node* _next) {
        val = _val;
        next = _next;
    }
};
*/

class Solution {
public:
    Node* insert(Node* head, int insertVal) {
        if (not head)
        {
            auto *node = new Node(insertVal);
            node->next = node;
            return node;
        }

        bool first_round = true;
        Node *node = head;

        while(first_round)
        {
            // CASE1
            // insert 4 or 5
            //
            //  node
            //   3--->5

            // CASE2
            // insert 0 or 1
            // insert 5
            //
            //  node
            //   4--->1  where is the smallest number

            // CASE3
            // insert 1 into [1]
            // insert 1 into [1, 1]

            // CASE4
            // insert 0 into [1], [1, 1]

            auto is_case1 = [&insertVal](Node *node) {
                return (node->val < insertVal and insertVal <= node->next->val);
            };

            auto is_case2 = [&insertVal](Node *node) {
                return (node->val > node->next->val) and
                       ((node->val > insertVal and insertVal <= node->next->val) or
                        (node->val < insertVal and insertVal > node->next->val));
            };

            auto is_case3 = [&insertVal](Node *node) {
                return node->val == insertVal && insertVal == node->next->val;
            };

            if (is_case1(node) || is_case2(node) || is_case3(node))
            {
                node->next = new Node(insertVal, node->next);
                return head;
            }

            node = node->next;

            if (node == head)
                first_round = false; // starting of second round
        }

        // CASE4
        head->next = new Node(insertVal, head->next);
        return head;
    }
};
