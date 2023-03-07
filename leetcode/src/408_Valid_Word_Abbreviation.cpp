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


// 408_Valid_Word_Abbreviation

// https://leetcode.com/problems/valid-word-abbreviation/description/

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr)
    {
        return method_1(word, abbr);
    }

private:
    bool method_1(string &word, string &abbr)
    {
        // TC
        // a, a,            aa
        // a, 1,            2, 1a, a1
        // abc, 2c, ab1     3c, 2cc, 2, a3, a2c

        int idx1 = 0;
        int idx2 = 0;

        while (idx1 < word.length() && idx2 < abbr.length())
        {
            if (islower(abbr[idx2]))
            {
                if (word[idx1] == abbr[idx2])
                {
                    idx1++;
                    idx2++;
                }
                else
                {
                    return false;
                }
            }
            else // digit
            {
                auto get_numbers = [&abbr](int i) -> int {
                    int start = i;
                    if (abbr[i] == '0') return -1;
                    for (; isdigit(abbr[i]); i++);
                    int end = i;    // exclusive

                    return stoi(abbr.substr(start, end-start));
                };

                int nums = get_numbers(idx2);
                if (nums == -1) return false;

                idx1 += nums;
                idx2 += (nums < 10 ? 1 : 2);

            }
        }

        return (idx1 == word.length() && idx2 == abbr.length());
    }
};
