#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 2_Add_Two_Numbers

// https://leetcode.com/problems/add-two-numbers/description/

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
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {

        int carry = 0;
        Node * head = nullptr;
        Node * tail = nullptr;

        while (l1 || l2)
        {
            auto v1 = l1 ? l1->val : 0;
            auto v2 = l2 ? l2->val : 0;

            int sum = v1 + v2 + carry;
            // REMEMBER
            // carry can also be calculated like the following:
            //      carry = sum / 10;
            carry = (sum >= 10 ? 1 : 0);

            if (! head)
            {
                // REMEMBER
                // Do not confuse sum / 10 and sum % 10
                head = tail = new Node(sum % 10, nullptr);
            }
            else
            {
                tail->next = new Node(sum % 10, nullptr);
                tail = tail->next;
            }

             if (l1) l1 = l1->next;
             if (l2) l2 = l2->next;
        }

        if (carry == 1)
        {
            tail->next = new Node(1, nullptr);
            tail = tail->next;
        }

        return head;

    }
};
