#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 70_Climbing_Stairs

// https://leetcode.com/problems/climbing-stairs/submissions/875031843/

// REMEMBER
// This can be solved using DP

class Solution {
public:
    int climbStairs(int n)
    {

        if (n == 1 || n == 2) return n;

        vector<int> s(n+1); // let's not use s[0] for simplicity
        s[1] = 1;
        s[2] = 2;

        for (int k = 3; k <= n; k++)
            s[k] = s[k-1] + s[k-2];

        return s[n];
    }
};
