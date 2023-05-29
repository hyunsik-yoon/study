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

// 2068_Check_Whether_Two_Strings_are_Almost_Equivalent
// https://leetcode.com/problems/check-whether-two-strings-are-almost-equivalent/description/

class Solution {
public:
    bool checkAlmostEquivalent(string word1, string word2) {
        int c_n = 'z' - 'a' + 1;
        vector<int> c1(c_n, 0), c2(c_n, 0);

        for (int i = 0; i < word1.length(); ++i)
        {
            int c_idx = word1[i] - 'a';
            ++c1[c_idx];
        }

        for (int i = 0; i < word2.length(); ++i)
        {
            int c_idx = word2[i] - 'a';
            ++c2[c_idx];
        }

        for (int i = 0; i < c1.size(); ++i)
        {
            if (std::abs(c1[i] - c2[i]) > 3) return false;
        }

        return true;
    }
};
