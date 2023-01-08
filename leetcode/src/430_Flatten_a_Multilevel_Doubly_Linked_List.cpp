#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 430_Flatten_a_Multilevel_Doubly_Linked_List
// https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/description/

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

// REMEMBER
// Linked list 문제는 head에 dummy node를 달고 시작하면 편할때가 많다. (물론 현실에서는 이 dummy 를 free해야 한다.)
//
// 여기서도 dummy를 달고 시작하면
//
//      current_node->next->prev = flatten_aux(currnet_node)
//
//식으로 flatten_aux 의 API를 구성할 수 있다.

namespace
{

struct List
{
    Node *head = nullptr;
    Node *tail = nullptr;
};

List flatten_aux(Node* root)
{
    if (not root) return List();

    Node *tail = nullptr;
    for (Node *node = root; node; node = node->next)
    {
        if (node->child)
        {
            List child_list = flatten_aux(node->child);

            // tail of child
            if (node->next)
            {
                child_list.tail->next = node->next;
                node->next->prev = child_list.tail;
            }
            // head of child
            child_list.head->prev = node;
            node->next = child_list.head;

            node->child = nullptr;
        }

        tail = node;
    }
    return List{.head = root, .tail = tail};
}

}; // namespace

class Solution {
public:
    Node* flatten(Node* head)
    {
        List list = flatten_aux(head);

        return list.head;
    }
};
