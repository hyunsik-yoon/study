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

// 232_Implement_Queue_using_Stacks

// https://leetcode.com/problems/implement-queue-using-stacks/description/

class MyQueue {
public:
    MyQueue() {

    }

    void push(int x) {
        // push into push_st
        push_st.push(x);
    }

    void process_when_pop_st_empty()
    {
        if (pop_st.empty())
        {
            while (!push_st.empty())
            {
                auto val = push_st.top();
                push_st.pop();
                pop_st.push(val);
            }
        }
    }

    int pop()
    {
        // move all in push_st to pop_st
        process_when_pop_st_empty();

        auto ret = pop_st.top();
        pop_st.pop();
        return ret;
    }

    int peek() {
        // move all in push_st to pop_st
        process_when_pop_st_empty();

        return pop_st.top();
    }

    bool empty()
    {
        return push_st.empty() && pop_st.empty();
    }

private:
    stack<int> push_st, pop_st;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
