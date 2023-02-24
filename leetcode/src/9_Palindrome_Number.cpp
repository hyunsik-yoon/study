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

// 9. Palindrome Number

// https://leetcode.com/problems/palindrome-number/description/

class Solution {
public:
    bool isPalindrome(int x)
    {
        // return get_answer_1(x);
        return get_answer_2(x);
    }

private:
    bool get_answer_1(int x)
    {
        if (x < 0) return false;

        string num = std::to_string(x);

        if (num.size() == 1) return true;

        string rev{num};
        std::reverse(rev.begin(), rev.end());

        return std::equal(num.begin(), num.begin() + num.size() / 2, rev.begin());
    }

    bool get_answer_2(int x)
    {
        if (x < 0) return false;
        if (x < 10) return true;

        auto get_digit = [](int x, int ten_power) {
            int reminder = x % (ten_power * static_cast<long>(10));
            return reminder / ten_power;
        };

        // TC   22   32123    1001

        auto is_pal = [&get_digit](int x, int big_ten_power) {

            int small_ten_power = 1;

            while (big_ten_power > small_ten_power)
            {
                if (get_digit(x, big_ten_power) != get_digit(x, small_ten_power)) return false;

                big_ten_power /= 10;
                small_ten_power *= 10;
            }

            return true;
        };

        long ten_power = 1;
        while (true)
        {
            if (x / ten_power == 0)
            {
                return is_pal(x, ten_power / 10);
            }

            ten_power *= 10;
        }
    }
};
