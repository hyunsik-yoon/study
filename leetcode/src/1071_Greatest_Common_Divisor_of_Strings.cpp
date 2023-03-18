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

// 1071_Greatest_Common_Divisor_of_Strings

// https://leetcode.com/problems/greatest-common-divisor-of-strings/description/

// 두 스트링 안에 gcd string 이 있다. 즉, str1 = (gcd_string)+, str2 = (gcd_string)+.
// gcd_string 을 리턴하라. 만일 gcd_string이 없으면 ""을 리턴.

class Solution {
public:
    string gcdOfStrings(string str1, string str2)
    {
        // return gcdOfStrings_o_n_square(str1, str2);
        return gcdOfStrings_from_solution(str1, str2);
    }

private:
    string gcdOfStrings_from_solution(string &str1, string &str2)
    {
        // REMEMBER
        //  gcd 로 이루어진 관계라면 이렇다고 한다.
        if (str1 + str2 != str2 + str1)
            return "";

        // REMEMBER
        //  gcd
        int g = std::gcd(str1.length(), str2.length());
        return string(str1.begin(), str1.begin() + g);
    }

    string gcdOfStrings_o_n_square(string &str1, string &str2)
    {
        // "A", "A"
        // "ABAB", "AB"
        // "ABABAB", "ABAB"
        // "LEET", "CODE"

        // this function has an error

        string &lo = str1.length() > str2.length() ? str1 : str2;
        string &sh = str1.length() > str2.length() ? str2 : str1;

        int len = sh.length();

        for (int l = len; l >= 1; l--)
        {
            bool found = false;

            if (sh.length() % l != 0) continue;
            if (lo.length() % l != 0) continue;

            // check short
            for (int k = 1; k < sh.length() / l; k++)
            {
                if (!std::equal(sh.begin(), sh.begin() + l,
                                  sh.begin() + l*k))
                {
                    found = false;
                    break;
                }
                else found = true;
            }

            if (!found) continue;
            found = false;

            // check long
            for (int k = 0; k < lo.length() / l; k++)
            {
                if (std::equal(sh.begin(), sh.begin() + l,
                               lo.begin() + l*k))
                    found = true;
                else
                {
                    found = false;
                    break;
                }
            }

            if (found) return string(sh.begin(), sh.begin() + l);
        }

        return "";
    }
};

