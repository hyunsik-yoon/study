#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/reverse-words-in-a-string-iii/description/

class Solution {
public:
    string reverseWords(string s) {
        return method_1(s);
    }

    string method_1(string &s)
    {
        for (int i = 0; i < s.length(); )
        {
            // REMEMBER
            int space = s.find(" ", i);

            if (space == i)
            {
                i++;
                continue;
            }
            // REMEMBER
            else if (space == string::npos) // end of string
            {
                if (s.length() - i <= 1) // nothing to do
                    break;

                std::reverse(s.begin() + i, s.end());
                break;
            }
            else // found a word
            {
                // REMEMBER
                std::reverse(s.begin() + i, s.begin() + space);
                i = space + 1;
            }
        }
        return s;
    }
};
