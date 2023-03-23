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

// 1323_Maximum_69_Number

// https://leetcode.com/problems/maximum-69-number/description/

class Solution {
public:
    int maximum69Number (int num)
    {
        // TC
        // 6, 9, 69, 96

        for (int x = 1000; x > 0; x /= 10)
        {
            int quotiont = num / x;
            if (quotiont == 0) continue;

            if (quotiont % 10 == 6)
            {
                return num + 3*x;
            }
        }

        return num;
    }
};
