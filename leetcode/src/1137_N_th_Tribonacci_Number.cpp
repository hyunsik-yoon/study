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

// 1137_N_th_Tribonacci_Number

// https://leetcode.com/problems/n-th-tribonacci-number/description/

class Solution {
public:
    int tribonacci(int n)
    {
        // T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

        vector<int> val{0, 1, 1};

        for (int k = 3; k <= n; k++)
        {
            val.emplace_back(val[k-1] + val[k-2] + val[k-3]);
        }

        return val[n];
    }
};
