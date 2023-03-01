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

// 231_Power_of_Two

// https://leetcode.com/problems/power-of-two/description/

// n 이 power of 2 (2의 재곱수) 인지 아닌지 리턴

class Solution {
public:
    bool isPowerOfTwo(int n)
    {
        // return method_with_gcc_builtin(n);
        return method_minus_1(n);

        // return method_reminder_recursive(n);
    }

    bool method_with_gcc_builtin(int n)
    {
        // REMEMBER
        //    just in case
        return __builtin_popcount(n) == 1;
    }

    bool method_minus_1(int n)
    {
        if (n <= 0) return false;

        // REMEMBER
        // when n = pow(2, x), the line below is true
        return (n & (n - 1)) == 0;
    }

    bool method_reminder_recursive(int n)
    {
        if (n <= 0) return false;
        if (n == 1) return true;
        if (n % 2 == 1) return false;

        return method_reminder_recursive(n/2);
    }
};
