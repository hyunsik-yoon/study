#include <algorithm>
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

// 125_Valid_Palindrome

// https://leetcode.com/problems/valid-palindrome/description/

// string s 에서 숫자와 문자만 남기고 문자는 모두 lowercase 로 바꾸고 나서...
// 뒤집을떄 같은 string이 되면 palindrome 이다. palindrome 인지 맞춰라.

class Solution {
public:
    bool isPalindrome(string s)
    {
        // return method_1_convert(s);
        // return method_2_reverse(s);
        return method_3_two_pointers(s);
    }

    bool method_3_two_pointers(string &s)
    {
        int len = s.length();

        int l = 0;
        int r = len - 1;

        while (l < len && r >= 0)
        {
            while (l < len && !isalnum(s[l])) l++;
            while (r >= 0 && !isalnum(s[r])) r--;

            if (!(l < len && r >= 0)) break;

            if (tolower(s[l]) != tolower(s[r])) return false;

            l++;
            r--;
        }

        return true;
    }

    bool method_2_reverse(string &s)
    {
        string s_reversed{s};
        std::reverse(s_reversed.begin(), s_reversed.end());

        int s_ind = 0;
        int r_ind = 0;

        while(s_ind < s.size() && r_ind < s.size())
        {
            // REMEMBER
            //      in <ctype.h>
            //          isalnum, isalpha, islower, isdigit,
            //          tolower, toupper
            while (s_ind < s.size() && !isalnum(s[s_ind])) s_ind++;
            while (r_ind < s.size() && !isalnum(s_reversed[r_ind])) r_ind++;

            if (s_ind == s.size() || r_ind == s.size()) break;

            if (tolower(s[s_ind]) != tolower(s_reversed[r_ind]))
                return false;

            s_ind++;
            r_ind++;
        }

        return true;
    }

    bool method_1_convert(string &s)
    {
        // for each ch in s
        //     convert ch to lowercase
        //     or remove it if it's alphanumeric
        // then check forward/backward

        // TC
        // "a"          true
        // "ab"         false
        // "aba"        true
        // "abc"        false
        string converted;

        for (char ch: s)
        {
            char alpha_diff = 'A' - 'a';
            if ('A' <= ch and ch <= 'Z')
            {
                const char lower_char = static_cast<char>(ch - alpha_diff);
                converted.append({lower_char});
            }
            else if (('0' <= ch and ch <= '9') || ('a' <= ch and ch <= 'z'))
            {
                converted.append({ch});
            }
        }

        cout << converted << endl;

        int len = converted.size();
        for (int k = 0; k < len/2; k++)
        {
            if (!(converted[k] == converted[len - 1 - k]))
                return false;
        }

        return true;
    }
};
