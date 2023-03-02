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

// 1762_Buildings_With_an_Ocean_View

// https://leetcode.com/problems/buildings-with-an-ocean-view/editorial/

class Solution {
public:
    vector<int> findBuildings(vector<int>& heights)
    {
        int highest_right = 0;
        vector<int> res;

        for (int k = heights.size() - 1; k >= 0; k--)
        {
            if (heights[k] > highest_right)
            {
                res.emplace_back(k);
                highest_right = heights[k];
            }
        }

        std::reverse(res.begin(), res.end());

        return res;
    }
};
