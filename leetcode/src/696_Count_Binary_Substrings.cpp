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

// 696_Count_Binary_Substrings
// https://leetcode.com/problems/count-binary-substrings/description/
//
// 1과 0으로 이루어진 string s의 substring 중,
// length 가 2m 이고,
// ch in s[0,m) == '0' and ch in s[m, 2m) == '1' 또는
// ch in s[0,m) == '1' and ch in s[m, 2m) == '0' 인 substring의 갯수는?
// 예를 들어, s = '1100011' 이면 답은 4('1100', '10', '0011', '01')

class Solution {
public:
    int countBinarySubstrings(string s)
    {
        int ret = 0;

        char prev_ch = s[0];
        int c_recent = 1;

        int c_old= 0;

        for (int k = 1; k < s.length(); ++k)
        {
            if (s[k] != s[k-1])
            {
                ret += std::min(c_recent, c_old);

                c_old = c_recent;
                c_recent = 1;
            }
            else
            {
                ++c_recent;
            }
        }

        ret += std::min(c_recent, c_old);

        return ret;
    }
};

/*
1

10101

00110011

*/
