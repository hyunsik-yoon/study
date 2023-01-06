#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 203_Remove_Linked_List_Elements

// https://leetcode.com/problems/remove-linked-list-elements/description/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeElements(ListNode* head, int val)
    {
        // TC
        // [], 1
        // [1] 1
        // [1, 1] 1  ---> 1)
        // [1, 2], 1 ---> 2)
        // [2, 1, 1], 1

        // REMEMBER
        // 처음에 prev와 node를 두려고 했으면
        // node가 두번째 ListNode를 가리키게 되므로....
        // node가 만일 첫번째 ListNode를 가리키게 되는 경우를 좀 더 고민해봐야 한다.

        while (head && head->val == val)
            head = head->next;

        if (! head)
            return nullptr;

        auto *prev = head;
        auto *node = head->next;

        for ( ; node ; )
        {
            if (node->val == val)
            {
                prev->next = node->next;
                node = prev->next;
            }
            else
            {
                node = node->next;
                prev = prev->next;
            }
        }
        return head;
    }
};