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

// 520_Detect_Capital
// https://leetcode.com/problems/detect-capital/description/

class Solution {
public:
    bool detectCapitalUse(string word) {

        if (word.length()  == 1) return true;

        constexpr int ALL_LOWER_CASE = 1;
        constexpr int ALL_UPPER_CASE = 2;
        constexpr int FIRST_UPPER_CASE = 3;

        int situation;

        if (islower(word[0]) && islower(word[1])) situation = ALL_LOWER_CASE;
        else if (isupper(word[0]) && islower(word[1])) situation = FIRST_UPPER_CASE;
        else if (isupper(word[0]) && isupper(word[0])) situation = ALL_UPPER_CASE;
        else return false;

        for (int k = 2; k < word.length(); ++k)
        {
            switch (situation)
            {
                case ALL_LOWER_CASE:
                case FIRST_UPPER_CASE:
                    if (isupper(word[k])) return false;
                    break;
                case ALL_UPPER_CASE:
                    if (islower(word[k])) return false;
                    break;
                default:
                    throw runtime_error("should not be here");
            }
        }
        return true;
    }
};
