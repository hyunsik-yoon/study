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


// 227_Basic_Calculator_II

// https://leetcode.com/problems/basic-calculator-ii/description/

class Solution {
public:
    int calculate(string s)
    {
        /*          num_st (나중에 elem 들을 다 더한다. 그러려면 - 연산은 sign - 로 바꾼다.)
        1           1
        2-1         2 -1
        4/3         1
        3-2*3       3 -2  => 3 -6
        3-2*3+3     3 -2  => 3 -6 => 3 -6  3

        REMEMBER

        첫번째 숫자를 push
        그 다음부터는....
            op를 저장
            숫자를 push 할 때 op가 *, / 이면 연산해서 push
                             op가 + 이면 그대로 push
                             op가 - 이면 -1*숫자를 push

        */

        stack<int> num_st;
        char op = '^'; // start
        int current = 0;
        for(int k = 0; k < s.length(); k++)
        {
            if (isdigit(s[k]))
                current = current*10 + (s[k] - '0');

            if ((!isspace(s[k]) && !isdigit(s[k])) || k == s.length() - 1)
            {
                if (op == '^') num_st.push(current);
                else if (op == '*' || op == '/')
                {
                    int n1 = num_st.top(); num_st.pop();
                    int n2 = current;

                    num_st.push(op == '*'? n1*n2 : n1/n2);
                }
                else if (op == '+')
                    num_st.push(current);
                else if (op == '-')
                    num_st.push(-1 * current);    // REMEMBER

                op = s[k];
                current = 0;
            }
        }

        int total_sum = 0;
        while(!num_st.empty())
        {
            int n1 = num_st.top();
            num_st.pop();

            total_sum += n1;
        }

        return total_sum;
    }
};
