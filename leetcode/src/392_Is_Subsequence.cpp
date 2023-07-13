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

// 392. Is Subsequence
//https://leetcode.com/problems/is-subsequence/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int sk = 0;
        int tk = 0;

        while (sk < s.length() && tk < t.length())
        {
            if (s[sk] == t[tk])
            {
                ++sk;
                ++tk;
            }
            else
            {
                tk++;
            }
        }

        if (sk == s.length())
            return true;
        else
            return false;
    }
};
