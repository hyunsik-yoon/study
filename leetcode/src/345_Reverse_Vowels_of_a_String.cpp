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

// 345_Reverse_Vowels_of_a_String

// https://leetcode.com/problems/reverse-vowels-of-a-string/description/

// 모음은 reverse하는 문제

class Solution {
public:
    string reverseVowels(string &s)
    {
        // TC
        // "a", "s"
        // "ao", "ss"
        // "aTo", , "Tao", "sas"

        int left = 0;
        int right = s.length() - 1;

        auto is_vowel = [](char c) -> bool {
            return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
                    c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
        };

        while (left < right)
        {
            for (; left < right && !is_vowel(s[left]); left++);
            for (; left < right && !is_vowel(s[right]); right--);

            if (left < right)
            {
                std::swap(s[left], s[right]);
                left++;
                right--;
            }
        }

        return s;
    }
};
