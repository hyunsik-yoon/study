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

// 695. Max Area of Island
// https://leetcode.com/problems/max-area-of-island/description/

#define VISITED 2

struct Pos
{
    int x, y;
};

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid)
    {
        return bfs_with_marking_visited(grid);
    }

    int bfs_with_marking_visited(vector<vector<int>>& g)
    {
        int max_area = 0;
        queue<Pos> q;

        for (int y = 0; y < g.size(); ++y)
        {
            for (int x = 0; x < g[0].size(); ++x)
            {
                if (g[y][x] != 1) continue;

                auto process_island = [&q, &g](int x, int y) {
                    q.push(Pos{x, y});
                    g[y][x] = VISITED;
                };

                int area = 0;
                process_island(x, y);

                while (!q.empty())
                {
                    auto pos = q.front();
                    q.pop();
                    ++area;

                    // T, B, L, R
                    if (pos.y > 0 && g[pos.y-1][pos.x] == 1) process_island(pos.x, pos.y-1);
                    if (pos.y < g.size() - 1 && g[pos.y+1][pos.x] == 1) process_island(pos.x, pos.y+1);
                    if (pos.x > 0 && g[pos.y][pos.x-1] == 1) process_island(pos.x-1, pos.y);
                    if (pos.x < g[0].size() - 1 && g[pos.y][pos.x+1] == 1) process_island(pos.x+1, pos.y);
                }
                max_area = std::max(area, max_area);
            }
        }

        return max_area;
    }
};

/*
[[0]]
[[0. 0],
 [0. 0]]

[[1]]
[[0. 2],
 [0. 2]]

[[1. 0. 0],
 [0. 1, 1]]


[[1,1,0,0,0],
 [1,1,0,0,0],
 [0,0,0,1,1],
 [0,0,0,1,1]]

*/
