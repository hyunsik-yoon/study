#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 206_Reverse_Linked_List

// https://leetcode.com/problems/reverse-linked-list/description/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
using Node = ListNode;

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // TC
        // []
        // [1,2,3]
        // return reverse_iterative(head);
        // return reverse_recursive_1(head);
        return reverse_recursive_2(head);
    }

    ListNode* reverse_iterative(ListNode* head)
    {
        Node *rev = nullptr;

        for (Node* node = head; node ; )
        {
            auto next_node = node->next;
            node->next = rev;
            rev = node;

            node = next_node;
        }
        return rev;
    }

    ListNode* reverse_recursive_1(ListNode* node)
    {
        // []
        // [1]
        // [1. 2]
        Node* reversed = nullptr;
        rev(node, reversed);
        return reversed;
    }

    void rev(Node* node, Node* &reversed)
    {
        if (! node)
            return;

        auto *next_node = node->next;
        node->next = reversed;
        reversed = node;

        rev(next_node, reversed);
    }

    ListNode* reverse_recursive_2(ListNode* node)
    {
        // REMEMBER
        //
        // 1 -> 2 -> 3 -> 4 -> null
        //
        // head points last node of the result of reversed_recursive_2() like the following !!
        //
        // head : 1 ----------------------------------+
        //                                           \|/
        // reverse_recursive_2(head->next) : 4 -> 3-> 2

        if (! node) return nullptr;
        else if (! node->next) return node;

        auto *new_tail = node;
        auto *rev = reverse_recursive_2(node->next);

        new_tail->next->next = new_tail;
        new_tail->next = nullptr;

        return rev;
    }

};
