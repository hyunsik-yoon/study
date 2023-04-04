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

// 921_Minimum_Add_to_Make_Parentheses_Valid

// https://leetcode.com/problems/minimum-add-to-make-parentheses-valid/description/

class Solution {
public:
    int minAddToMakeValid(string s)
    {
        // increase when stack is empty and char is ')'
        int closing = 0;
        int opening = 0;

        for (char ch : s)
        {
            if (ch == '(') ++opening;
            else // ch == )
            {
                if (opening == 0)
                {
                    ++closing;
                }
                else // opening > 0
                {
                    --opening;
                }
            }
        }

        return opening + closing;
    }
};

/*

REMEMBER
    I couldn't thought about the following case:
        ( ) ) ) ( (

    because I couldn't find out ()() is a valid parenthesis string,
    meaning that I couldn't enumerate cases from the second bullet.

    So, with such context free grammar,
    try to enumerate all the possible patterns.
*/
