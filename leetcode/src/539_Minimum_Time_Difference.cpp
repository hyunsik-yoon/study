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

// 539. Minimum Time Difference
// https://leetcode.com/problems/minimum-time-difference/description/

class Solution {
public:
    int findMinDifference(vector<string>& timePoints) {
        // normalize to minutes
        // sort
        // calculate tp[i] & tp[i+1] (for 0<= i < length())
        // calculate tp[0] & tp[last] (for 0<= i < length())

        vector<int> mins;

        for (const string &hhmm: timePoints)
        {
            int hh = std::atoi(hhmm.substr(0, 2).data());
            int mm = std::atoi(hhmm.substr(3, 2).data());

            mins.push_back(hh*60 + mm);
        }

        sort(mins.begin(), mins.end());

        int min_diff = 60*24 + 1;

        for (int i = 0; i < mins.size() - 1; ++i)
        {
            int cur_diff = mins[i+1] - mins[i];
            min_diff = std::min(min_diff, cur_diff);
        }

        int first_one = mins[0] + 24*60;
        min_diff = std::min(min_diff, first_one - mins[mins.size() - 1]);

        return min_diff;
    }
};
/*
 [0 1439]


*/
