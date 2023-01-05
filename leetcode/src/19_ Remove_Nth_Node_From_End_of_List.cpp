#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 19_ Remove_Nth_Node_From_End_of_List

// https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/

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
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        // return method_2_pass(head, n);
        return method_1_pass_two_pointers(head, n);
    }

    // REMEMBER
    // Approach 1. Better one. time complexity = O(n)
    ListNode* method_1_pass_two_pointers(ListNode* head, int n)
    {
        ListNode *to_tail = head;
        // move n
        for (int k = 0; k < n; k++)
            to_tail = to_tail->next;

        if (to_tail == nullptr) // which means that n points head
            return head->next;

        ListNode *to_prev = head;

        for ( ; to_tail->next != nullptr; to_tail = to_tail->next)
            to_prev = to_prev->next;

        to_prev->next = to_prev->next->next;

        return head;
    }

    // Approach 2. Better one. time complexity = O(2n)
    ListNode* method_2_pass(ListNode* head, int n)
    {
        auto length = [](ListNode* head) {
            int count = 0;
            for (ListNode* node = head; node; node = node->next)
                count++;
            return count;
        };

        // 1 base
        auto get_node = [](ListNode* node, int n) {
            int count = 1;
            for (; count < n; node = node->next)
                count++;
            return node;
        };

        int len = length(head);

        if (len == n)
        {
            head = head->next;
            return head;
        }

        auto *prev = get_node(head, len - n);

        auto *del = prev->next;
        prev->next = del->next;

        // delete del;

        return head;
    }
};
