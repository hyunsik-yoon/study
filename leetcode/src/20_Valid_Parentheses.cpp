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

// 20_Valid_Parentheses

// https://leetcode.com/problems/valid-parentheses/description/

class Solution {
public:
    bool isValid(string s) {
        std::stack<char> st;

        if (s.length() % 2 != 0) return false;

        for (auto ch: s)
        {
            if (ch == '(' || ch == '{' || ch == '[')
            {
                st.push(ch);
            }
            else
            {
                if (st.empty()) return false;

                char opening_ch = st.top();
                st.pop();

                // REMEMBER
                switch (ch)
                {
                    case '}':
                        if (opening_ch != '{') return false;
                        break;
                    case ')':
                        if (opening_ch != '(') return false;
                        break;
                    case ']':
                        if (opening_ch != '[') return false;
                        break;
                }
            }
        }

        return st.empty();
    }
};

/*
REMEMBER

stack API is different from queue API

stack:
    st.push(val);
    val = st.top();     // not front or back
                        // undefined if st.empty() == true
    st.pop(val);

queue:
    q.push(val);        // just like vector::emplace_back()
    val = q.front();    // undefined if st.empty() == true
    val = q.back();     // undefined if st.empty() == true

    q.pop()             // removes front

*/
