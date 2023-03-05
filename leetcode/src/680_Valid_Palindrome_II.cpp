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

// 680. Valid Palindrome II
// https://leetcode.com/problems/valid-palindrome-ii/description/

// 문자가 palindrom 인가? 만일 palindrom 이 아니라면 한글자 지우고 따져봐도 된다.

class Solution {
public:
    bool validPalindrome(string s)
    {
        // TC
        // "s", "aab", "abca"

        int last = s.length() - 1;

        // return is_pal(s, 0, last, false);    // recursive
        return is_pal_iter(s);

    }

private:
    bool is_pal(string &s, int st, int end, bool deleted_one)
    {
        // TC
        // "", "s", "aa", "caabc", "abca"

        // for n length string
        // time when s is palindrom, O(n)
        // time when s is not a palindrom, O(n)
        // space : O(n)

        if (st > end) return true;

        if (st == end) // one char
            return true;

        if (s[st] != s[end])
        {
            if (deleted_one) return false;

            deleted_one = true;

            if (is_pal(s, st + 1, end, deleted_one)) return true;
            else if (is_pal(s, st, end - 1, deleted_one)) return true;
            else return false;
        }
        else
            return is_pal(s, st + 1, end - 1, deleted_one);
    }

    bool is_pal_iter(string &s)
    {
        auto is_pal = [&s](int st, int end) -> bool {
            while(st <= end)
            {
                if (s[st] != s[end]) return false;

                st++;
                end--;
            }
            return true;
        };

        int st = 0;
        int end = s.length() - 1;

        while (st <= end)
        {
            if (s[st] != s[end])
                return is_pal(st + 1, end) || is_pal(st, end -1);

            st++;
            end--;
        }
        return true;
    }
};
