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

// 693_Binary_Number_with_Alternating_Bits

// https://leetcode.com/problems/binary-number-with-alternating-bits/description/

class Solution {
public:
    bool hasAlternatingBits(int n)
    {
        while (n >> 1 != 0)
        {
            if ((n & 1) ^ ((n >> 1) & 1) != 1) return false;

            n = n >> 1;
        }

        return true;
    }
};

/*
0000001
0000010

0101

negative

0000011
0000100
*/
