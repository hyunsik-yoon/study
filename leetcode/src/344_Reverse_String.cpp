#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/reverse-string/description/

class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int x = 0, y = s.size() - 1; y > x; x++, y--)
        {
            std::swap(s[x], s[y]);
        }
    }
};
