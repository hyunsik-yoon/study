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

// 973_K_Closest_Points_to_Origin

// https://leetcode.com/problems/k-closest-points-to-origin/description/

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k)
    {
        auto compare = [](vector<int> &a, vector<int> &b) {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };

        std::sort(points.begin(), points.end(), compare);

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }
};
