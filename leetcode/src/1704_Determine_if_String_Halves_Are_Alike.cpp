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

// 1704_Determine_if_String_Halves_Are_Alike
// https://leetcode.com/problems/determine-if-string-halves-are-alike/description/

class Solution {
public:
    bool halvesAreAlike(string s)
    {
        int s1 = 0, s2 = s.length() / 2;
        int vc1 = 0, vc2 = 0;

        for (int k = 0; k < s.length() / 2; ++k)
        {
            if (is_vowel(s[s1 + k])) ++vc1;
            if (is_vowel(s[s2 + k])) ++vc2;
        }

        return vc1 == vc2;
    }

    bool is_vowel(char c)
    {
        return c == 'a' ||
        c == 'e' ||
        c == 'i' ||
        c == 'o' ||
        c == 'u' ||
        c == 'A' ||
        c == 'E' ||
        c == 'I' ||
        c == 'O' ||
        c == 'U';
    }
};
