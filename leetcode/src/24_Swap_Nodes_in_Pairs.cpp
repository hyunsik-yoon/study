#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 24_Swap_Nodes_in_Pairs

// https://leetcode.com/problems/swap-nodes-in-pairs/submissions/

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
    ListNode* swapPairs(ListNode* head) {
        // TC
        // []
        // [1]
        // [1,2]
        // [1,2,3]
        // [1,2,3,4]
        proceed_swapping(head);

        return head;
    }

    void proceed_swapping(ListNode* &node)
    {
        if (not node || not node->next)
            return;

        // swap two nodes after node
        auto a = node;
        auto b = a->next;
        a->next = b->next;
        node = b;
        b->next = a;

        proceed_swapping(node->next->next);
    }
};
