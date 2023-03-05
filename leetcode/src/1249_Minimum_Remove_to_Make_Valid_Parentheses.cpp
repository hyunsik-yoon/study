#include <algorithm>
#include <cassert>
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

/*
1249_Minimum_Remove_to_Make_Valid_Parentheses

https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/description/

이상한 괄호가 있으면 없애는 문제

e.g., "a)b(c)d(e" ==> "ab(c)de"
*/

class Solution {
public:
    string minRemoveToMakeValid(string s)
    {
        /*
        push '('
        when meeting ')', pop
            if popped one is '(', ok
            if stack is empty, remove ')'

        at then end, check if stack is empty
        if not, remove all '(' in the stack
        */

        // TC
        // ''
        // ()
        // ())
        // (()
        // )())
        // ab(ab)ab
        // ab(ab)a)b

        if (s.empty()) return "";

        char REMOVE = 'R';

        stack<int> st;
        for (int k = 0; k < s.length(); k++)
        {
            if (isalpha(s[k])) continue;
            else if (s[k] == '(') st.push(k);
            else if (s[k] == ')')
            {
                if (st.empty())
                    s[k] = REMOVE;
                else
                    st.pop();
            }
        }

        while (! st.empty())
        {
            int k = st.top();
            st.pop();

            s[k] = REMOVE;
        }

        string res;

        for (int k = 0; k < s.length(); k++)
        {
            if(s[k] != REMOVE)
                res.append(1, s[k]);
        }

        return res;
    }
};
