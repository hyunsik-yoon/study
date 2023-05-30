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

// 1200. Minimum Absolute Difference
// https://leetcode.com/problems/minimum-absolute-difference/description/

class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr)
    {
        sort(arr.begin(), arr.end());

        vector<vector<int>> ret;
        int min_diff = arr[arr.size() - 1] - arr[0];

        for (int i = 0; i < arr.size() - 1; ++i)
        {
            int diff = arr[i+1] - arr[i];

            if (diff > min_diff) continue;
            else if (diff == min_diff)
            {
                ret.push_back({arr[i], arr[i+1]});
            }
            else // diff < min_diff
            {
                min_diff = diff;
                ret.clear();
                ret.push_back({arr[i], arr[i+1]});
            }
        }

        return ret;
    }
};
