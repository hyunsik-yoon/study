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

// 1833_Maximum_Ice_Cream_Bars
// https://leetcode.com/problems/maximum-ice-cream-bars/description/

class Solution {
public:
    int maxIceCream(vector<int>& costs, int coins)
    {
        int min_cost = 100000;
        int max_cost = 1;

        if (costs.size() == 1) return coins > costs[0] ? 1 : 0;

        for_each(costs.begin(), costs.end(),
            [&min_cost, &max_cost](int cost) {
                if (cost < min_cost) min_cost = cost;
                if (cost > max_cost) max_cost = cost;
            });

        cout << max_cost << "-" << min_cost << endl;
        vector<int> sorted_costs(max_cost - min_cost + 1, 0);

        for (int cost : costs)
        {
            ++sorted_costs[cost - min_cost];
        }

        int ice_creams = 0;
        for (int normalized_cost = 0; normalized_cost < sorted_costs.size(); ++normalized_cost)
        {
            int count = sorted_costs[normalized_cost];
            if (count == 0) continue;

            int cost = normalized_cost + min_cost;

            int how_many = coins / cost;

            if (how_many == 0) break;
            else if (how_many >= count) {
                ice_creams += count;
                coins -= (cost * count);
            }
            else { // how_many < count
                ice_creams += how_many;
                break;
            }
        }

        return ice_creams;
    }
};
/*

[10,6,8,7,7,8]

n 0 1 2 3 4
a 6 7 8 9 10
c 2 2 2 0 1

coins = 13


*/
