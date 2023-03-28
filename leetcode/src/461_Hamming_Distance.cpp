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

// 461_Hamming_Distance

// https://leetcode.com/problems/hamming-distance/submissions/

class Solution {
public:
    int hammingDistance(int x, int y)
    {
        int count = 0;

        int l = x > y ? x : y;
        int s = x > y ? y : x;

        while (l > 0)
        {
            int l_bit = l & 0b1;
            int s_bit = s & 0b1;

            if (l_bit ^ s_bit == 1) count++;

            l = l >> 1;
            s = s >> 1;
        }

        return count;
    }
};
