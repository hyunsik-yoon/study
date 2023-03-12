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
        return method_nlogn(points, k);
        return method_nlogk(points, k);
    }

private:
    vector<vector<int>> method_nlogn(vector<vector<int>>& points, int k)
    {
        auto compare = [](vector<int> &a, vector<int> &b) {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };

        std::sort(points.begin(), points.end(), compare);

        return vector<vector<int>>(points.begin(), points.begin() + k);
    }

    vector<vector<int>> method_nlogk(vector<vector<int>>& points, int k)
    {
        // maintain maxheap of size k
        auto compare = [](vector<int> &a, vector<int> &b) {
            return a[0]*a[0] + a[1]*a[1] < b[0]*b[0] + b[1]*b[1];
        };

        // REMEMBER
        //      heap
        vector<vector<int>> ans;
        make_heap(ans.begin(), ans.end(), compare);

        // maintain ans of size k
        for (auto &point : points)
        {
            // place new item at the end
            ans.emplace_back(point);
            // heapify
            push_heap(ans.begin(), ans.end());

            if (ans.size() > k)
                pop_heap(ans.begin(), ans.end());   // ans.front()를 삭제후 heapify
            // Note: 제일 큰 값을 가져오려면
            // ans.front() 를 보면 됨.
        }

        return ans;
    }
};
