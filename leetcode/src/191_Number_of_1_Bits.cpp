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

// 191_Number_of_1_Bits

// https://leetcode.com/problems/number-of-1-bits/solutions/

// 입력을 2진수로 표현할 때 1이 몇개 있나.

class Solution {
public:
    int hammingWeight(uint32_t n)
    {
        int num = 0;
        for (int k = 0; k < 32; k++)
        {
            if ((n & 1) == 1) num++;
            n = n >> 1;
            // REMEMBER
            // 실수. n = n >> 2 라고 했다. 왜 그랬는지... ㅎㅎㅎ
        }
        return num;
    }
};
