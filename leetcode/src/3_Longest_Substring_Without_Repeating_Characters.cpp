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

// 3. Longest Substring Without Repeating Characters

// https://leetcode.com/problems/longest-substring-without-repeating-characters/description/

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.length() == 0) return 0;

        int max_len = 1;
        int cur_len = 0;

        int start = 0;

        unordered_map<char, int> appeared;

        for (int i = 0; i < s.length(); ++i)
        {
            auto found = appeared.find(s[i]);
            if (found == appeared.end())
            {
                ++cur_len;
            }
            else
            {
                max_len = std::max(max_len, cur_len);

                int prev_start = start;
                start = found->second + 1;
                cur_len = i - start + 1;

                // remove chars from map
                for (char a : string(s.begin() + prev_start, s.begin() + start))
                    appeared.erase(a);
            }
            appeared[s[i]] = i;
        }

        max_len = std::max(max_len, cur_len);

        return max_len;
    }
};

/*
a b
0 1

i               0   1
max_len     1
cur_len     0   1   2
start       0

map
a:0
b:1
c:2

*/
