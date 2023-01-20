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

// 739_Daily_Temperatures

// https://leetcode.com/problems/daily-temperatures/description/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures)
    {
        // TC
        // [50]
        // [50, 51]
        // [51, 50]
        // [51, 51]
        // [51, 53, 52, 50]

        vector<int> &t = temperatures;

        stack<int> tbd;
        vector<int> ans(t.size(), -1);

        tbd.push(0);

        for (int k = 1; k < t.size(); k++)
        {
            // process previous temperatures
            while (! tbd.empty())
            {
                int prev = tbd.top();
                if (t[prev] < t[k])
                {
                    ans[prev] = k - prev;
                    tbd.pop();
                }
                else
                {
                    break;
                }
            }

            tbd.push(k);
        }

        // REMEMBER
        // The code below could be removed if we initialize answer with '0'

        // the ones in stack does not have warmer temperatures
        while (! tbd.empty())
        {
            int prev = tbd.top();
            tbd.pop();

            ans[prev] = 0;
        }

        return ans;
    }
};
