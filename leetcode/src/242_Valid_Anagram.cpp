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

// 242_Valid_Anagram

// https://leetcode.com/problems/valid-anagram/description/

// 소문자만으로 이루어진 string s를 뒤섞으면 string t가 나오나.

class Solution {
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;

        // return method1(s, t);
        return method2(s, t);
    }

private:
    bool method1(string &s, string &t)
    {
        // sort

        // time: O(n logn)
        // space: O(1)
        std::sort(s.begin(), s.end());
        std::sort(t.begin(), t.end());
        return std::equal(s.begin(), s.end(), t.begin());
    }

    bool method2(string &s, string &t)
    {
        // counter

        // time: O(n)
        // space: O(1)
        vector<int> counter('z'-'a'+1, 0);

        for (char ch: s)
            counter[ch-'a']++;

        for (char ch: t)
            counter[ch-'a']--;

        for (int count: counter)
            if (count != 0) return false;

        return true;
    }
};
