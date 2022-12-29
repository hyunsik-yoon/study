#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/spiral-matrix/description/

// REMEMBER
// Think carefully with cases when to finish to loop

struct Rect
{
    int x, y;
    int w, h;
};

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& m) {

        vector<int> path;

        int w = m[0].size();
        int h = m.size();

        Rect rect{0, 0, w, h};

        while (rect.w > 0 && rect.h > 0)
        {
            walk(rect, m, path); // walk on the edge of rectangle
            rect = shrink(rect); // get the next rectangle by removing four walked edges
        }

        return path;
    }

private:
    void walk(const Rect &rect, const vector<vector<int>>& m, vector<int> &path)
    {
        for (int x = rect.x; x < rect.x + rect.w; ++x) // to the right
            path.emplace_back(m[rect.y][x]);

        for (int y = rect.y + 1; y < rect.y + rect.h - 1; ++y) // the the bottom-1
            path.emplace_back(m[y][rect.x + rect.w - 1]);

        if (rect.h >= 2) // when rect h == 1, this edge is already done by the above for loop with x
            for (int x = rect.x + rect.w - 1; x >= rect.x; --x) // to the left
                path.emplace_back(m[rect.y + rect.h - 1][x]);

        if (rect.w >= 2) // when rect w == 1, this edge is already done by the above for loop with y
            for (int y = rect.y + rect.h - 2; y >= rect.y + 1; --y) // to the top-1
                path.emplace_back(m[y][rect.x]);

    }

    Rect shrink(const Rect &rect)
    {
        return Rect{rect.x + 1, rect.y + 1, rect.w - 2, rect.h - 2};
    }
};
