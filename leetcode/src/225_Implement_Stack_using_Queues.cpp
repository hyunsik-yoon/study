#include <algorithm>
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

// 225_Implement_Stack_using_Queues

// https://leetcode.com/problems/implement-stack-using-queues/submissions/

class MyStack {
public:
    MyStack(): helper_q(std::make_unique<std::queue<int>>()), data_q(std::make_unique<std::queue<int>>())
    {
    }

    void push(int x)
    {
        assert(helper_q->empty());

        // swap helper_q and data_q
        auto tmp = std::move(data_q);
        data_q = std::move(helper_q);
        helper_q = std::move(tmp);

        // after pushing the new data on top,
        data_q->push(x);

        // copy old data in helper_q to data_q
        while (! helper_q->empty())
        {
            auto val = helper_q->front();
            helper_q->pop();

            data_q->push(val);      // real_q has data ; buf_q is empty
        }
    }

    int pop()
    {
        auto val = data_q->front();
        data_q->pop();

        return val;
    }

    int top()
    {
        auto val = data_q->front();
        return val;
    }

    bool empty()
    {
        return data_q->empty();
    }

private:
    unique_ptr<queue<int>> helper_q, data_q;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
