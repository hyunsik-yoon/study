#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 509_Fibonacci_Number
// https://leetcode.com/problems/fibonacci-number/description/
class Solution {
public:
    int fib(int n) {
        if (n == 0) return 0;
        if (n == 1) return 1;

        int val_1 = 0, val_2 = 0;

        auto found_1 = cache.find(n - 1);
        if (found_1 == cache.end())
        {
            val_1 = fib(n - 1);
            cache[n - 1] = val_1;
        }
        else
        {
            val_1 = found_1->second;
        }

        auto found_2 = cache.find(n - 2);
        if (found_2 == cache.end())
        {
            val_2 = fib(n - 2);
            cache[n - 2] = val_2;
        }
        else
        {
            val_2 = found_2->second;
        }

        return val_1 + val_2;
    }

private:
    map<int, int> cache;
};
