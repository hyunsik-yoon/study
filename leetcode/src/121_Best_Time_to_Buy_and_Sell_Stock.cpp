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

// 121_Best_Time_to_Buy_and_Sell_Stock

// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

class Solution {
public:
    int maxProfit(vector<int>& prices)
    {
        int prev_min = prices[0];
        int max_profit = 0;

        for (int k = 1; k < prices.size(); k++)
        {
            prev_min = std::min(prices[k-1], prev_min);
            max_profit = std::max(prices[k] - prev_min, max_profit);
        }

        return max_profit;
    }
};
