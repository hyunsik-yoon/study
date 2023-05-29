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

// 997_Find_the_Town_Judge
// https://leetcode.com/problems/find-the-town-judge/description/

class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust)
    {
        if (n == 1) return 1;

        vector<int> trusted_c(n, 0);
        vector<bool> trusters(n, false);

        for (int k = 0; k < trust.size(); ++k)
        {
            int truster = trust[k][0];
            int trustee = trust[k][1];

            ++trusted_c[trustee - 1];

            trusters[truster - 1] = true;
        }

        int judge_count = 0;
        for (int i = 0; i < n; ++i)
            if (trusters[i] == false) ++judge_count;

        if (judge_count != 1) return -1;

        for (int i = 0; i < n; ++i)
            if (trusted_c[i] == n-1) return i + 1;

        return -1;
    }
};

/*
n = 100;
[[i (i < 100), i+ 1], [i (i > 1), i-1], [i (i < 100), 100], [100, 1]]
*/
