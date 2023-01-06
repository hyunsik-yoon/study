#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 21_Merge_Two_Sorted_Lists

// https://leetcode.com/problems/merge-two-sorted-lists/description/

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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
    {
        return iterative_way(list1, list2);
        // return recursive_way(list1, list2);
    }

    // REMEMBER
    // Recursive 방식도 가능
    ListNode* recursive_way(ListNode* list1, ListNode* list2)
    {
        if (not list1) return list2;
        if (not list2) return list1;

        if (list1->val < list2->val)
        {
            Node *head = list1;
            head->next = recursive_way(list1->next, list2);
            return head;
        }
        else
        {
            Node *head = list2;
            head->next = recursive_way(list1, list2->next);
            return head;
        }
        throw std::runtime_error("Should not reach here");
    }

    ListNode* iterative_way(ListNode* list1, ListNode* list2)
    {
        // TC
        // [], []
        // [1], [2]
        // [1,3], [2, 4, 5]
        Node *head = nullptr;
        Node *tail = nullptr;

        // REMEMBER
        // 새로운 링크드 리스트를 만드는데는 항상 head, tail 관리가 어려운데
        // 여기도 그렇다.
        // Solution 에 보면 이 부하를 없애려고
        // head = tail = new ListNode(DUMMY);
        // 를 만들고 시작한다.
        // 나중에 head->next 를 결과값으로 리턴하는 형식. 좀 꽁스.

        // REMEMBER
        // 노드를 tail에 붙인 후 node->next == nullptr 을 생략해도 문제는 없다. 계속 다음노드를 붙이면서 마지막에 nullptr 이 결국 붙으니까.
        // 취향문제.

        if (not list1) return list2;
        if (not list2) return list1;

        // making head
        if (list1->val < list2->val)
        {
            head = tail = list1;
            list1 = list1->next;
            head->next = nullptr;
        }
        else
        {
            head = tail = list2;
            list2 = list2->next;
            head->next = nullptr;
        }

        while(list1 && list2)
        {
            if (list1->val < list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
                tail = tail->next;
                tail->next = nullptr;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
                tail = tail->next;
                tail->next = nullptr;
            }
        }

        tail->next = (list1? list1 : (list2 ? list2: nullptr));

        return head;
    }
};
