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

// 17. Letter Combinations of a Phone Number
// https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits == "") return {};

        vector<string> ans;
        gen_digit(digits, 0, "", ans);

        return ans;
    }

    void gen_digit(const string &digits, int index, string s, vector<string> &ans)
    {
        static map<char, string> n2c =
            {{'2', "abc"}, {'3',"def"}, {'4',"ghi"}, {'5',"jkl"},
             {'6',"mno"}, {'7',"pqrs"}, {'8',"tuv"}, {'9',"wxyz"}};

        if (index == digits.length()) {
            ans.emplace_back(s);
            return;
        }

        const string &alphas = n2c[digits[index]]; // e.g., "abc"

        for (char c : alphas)
        {
            gen_digit(digits, index + 1, s + c, ans);
        }
    }

};

/*
23

a         b          c
d  e  f


*/
