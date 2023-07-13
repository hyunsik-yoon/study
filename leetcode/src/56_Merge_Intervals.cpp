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

// 56_Merge_Intervals
// https://leetcode.com/problems/merge-intervals/description/

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& times)
    {
        // sort by starting time
        //
        // for i and i+1
        //   check if both can be merged
        //      if so, merge them and make it i, then continue
        //      else
        //        start checking i+1 and i+2

        if (times.size() == 1) return times;

        sort(times.begin(), times.end(),
             [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; }); // ascending

        vector<vector<int>> ans;

        vector<int> current = times[0];

        for (int k = 1; k < times.size(); ++k)
        {
            // if mergeable
            if (current[1] >= times[k][0])
            {
                if (current[1] < times[k][1])
                    current[1] = times[k][1];
                // else, we will current includes times[k]
            }
            else
            {
                ans.emplace_back(current);
                current = times[k];
            }
        }
        ans.emplace_back(current);

        return ans;
    }
};
/*
[[1,4],[4,5], [6,8]]

current :[1,5]
ans :

*/
