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


// 5_Longest_Palindromic_Substring

// https://leetcode.com/problems/longest-palindromic-substring/description/

// string 안에 있는 가장 긴 palindrom 을 구하라. palindrom 이란... 반 접으면 동일한 스트링. 예) "abba", "abccba"

class Solution {
public:
    string longestPalindrome(string s)
    {
        // return get_palindrom_after_checking_left_and_right(s);
        return get_palindrom_dp(s);
    }

    string get_palindrom_after_checking_left_and_right(string &s)
    {
        /*
        for each i
            compare left part of i and right part of i (i-k, i+k)
            also,
            compare i-k and i+1+k
        */

        // test case: "a", "ab", "aa", "daba", "daac"

        int count = 1;
        int start = 0, end = 0;

        for (int i = 0; i < s.length(); i++)
        {
            // case 1
            {
                // REMEMBER
                //      think again we should initialize the initial count
                //      in this case, we pick one char at index i. then compare s[i-1] == s[i+1], and so on.
                //      therefore, initial length should be 1
                int count_here = 1;
                int k = 1;
                for (; (0 <= i - k) && (i + k <= s.length() - 1); k++)
                {
                    if (s[i-k] == s[i+k])
                    {
                        // REMEMBER
                        //      think again how much we need to increse... initially I wrong count_here++
                        //      in this case, we pick one char at index i. then compare s[i-1] == s[i+1], and so on.
                        //      therefore we need to increase by 2
                        count_here += 2;
                        if (count < count_here)
                        {
                            count = count_here;

                            // REMEMBER
                            //      아래 두 줄을 for 바깥에 썼다가 out of range 에러를 맞았다.
                            //      왜? for loop의 조건이 fail 되면 또는 아래아래의 elase break 로 빠지면 이미 k 가 증가해 있음
                            start = i-k;
                            end = i+k;
                        }
                    }
                    else break;
                }
            }
            // case 2
            {
                // REMEMBER
                //      think again we should initialize the initial count
                //      in this case, we pick one char at index i. then compare s[i] == s[i+1], and so on. (to decide string like "aa" as palindrom)
                //      therefore, initial length should be 0
                int count_here = 0;
                int k = 0;
                for (; (0 <= i - k) && (i + 1 + k <= s.length() - 1); k++)
                {
                    if (s[i-k] == s[i+1+k])
                    {
                        count_here += 2;
                        if (count < count_here)
                        {
                            count = count_here;
                            start = i-k;
                            end = i+1+k;
                        }
                    }
                    else break;
                }
            }
        }

        return s.substr(start, end - start + 1);
    }

    string get_palindrom_dp(string &s)
    {
        // REMEMBER dp 방식도 있다.
        return "a";
    }
};
