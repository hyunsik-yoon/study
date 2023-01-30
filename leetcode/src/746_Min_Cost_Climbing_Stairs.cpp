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

// 746_ Min_Cost_Climbing_Stairs

// https://leetcode.com/problems/min-cost-climbing-stairs/description/

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost)
    {
        vector<int> sum(cost.size() + 1, -1); // let's include top

        // TC
        // [1, 2]
        // [1, 2, 3, 4]

        // total cost to n'th step
        // sum[n] = sum[n-1] < sum[n-2] ? sum[n-1] : sum[n-2];

        sum[0] = sum[1] = 0;

        for (int k = 2; k < sum.size(); k++)
        {
            int cost_m1 = sum[k-1] + cost[k-1];
            int cost_m2 = sum[k-2] + cost[k-2];

            // REMEMBER std::min
            sum[k] = std::min(cost_m1, cost_m2);
        }

        return sum[sum.size() - 1];
    }
};
