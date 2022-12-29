#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/find-the-index-of-the-first-occurrence-in-a-string/description/

/*
REMEMBER

1. very simple solution:

     int strStr(string haystack, string needle) {
        return haystack.find(needle);

2. calling the following inside loop may slow down loop but worthy to remember.

    needle_len = needle.length();
    if (haystack.substr(i, needle_len) == needle) ...
*/

class Solution {
public:
    int strStr(string haystack, string needle) {
        return method_1(haystack, needle);
    }

private:
    int method_1(string &haystack, string &needle)
    {
        // TC
        // "a", "a"
        // "abcd", "abcd"
        // "abcde", "abcd"
        // "abc", "12345678"

        const string &l = haystack; // l means long string
        const string &s = needle;   // s means substring

        if (l.length() < s.length())
            return -1;

        for (int i = 0; i <= l.length() - s.length(); i++)
        {
            bool found = true;

            if (early_check(l, i, s) == false)
                continue;

            if (contain(l, i, s) == true)
                return i;
        }

        return -1;
    }

    bool contain(const string &l, int i, const string &s)
    {
        for (int j = 0; j < s.length(); j++)
        {
            if (l[i+j] != s[j])
                return false;
        }
        return true;
    }

    bool early_check(const string &l, int i, const string &s)
    {
        if (s.length() > 10)
        {
            int last = s.length() - 1;
            if (! (l[i] == s[0] && l[i+last] == s[last] && l[i+last/2] == s[last/2]))
                return false;
        }
        return true;
    }
};
