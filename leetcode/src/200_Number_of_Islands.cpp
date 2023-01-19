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

// ADD URL

// Insert code

// 200_Number_of_Islands

// https://leetcode.com/problems/number-of-islands/description/

// REMEMBER
//      an island in a 2x2 board can be considered as a graph

class Solution {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        // REMEMBER
        //  q.push(1);       1
        //  q.push(2);       1, 2
        //  q.push(3);       1, 2, 3
        //  f = q.front()    1
        //  f = q.back()     3
        //  q.pop()          2, 3

        std::queue<Point> q;
        int count = 0;

        for (int y = 0; y < grid.size(); y++)
        {
            for (int x = 0; x < grid[0].size(); x++)
            {
                if (grid[y][x] == '1')
                {
                    count++;

                    q.push(Point{.x = x, .y = y});
                    grid[y][x] = VISITED;

                    while (!q.empty())
                    {
                        Point &pt = q.front();
                        q.pop();

                        process_adjacent(grid, pt, q);
                    }
                }
            }
        }
        return count;
    }

private:
    struct Point
    {
        int x, y;
    };

    static const char VISITED = '2';

    void process_adjacent(vector<vector<char>>& grid, Point &pt, std::queue<Point> &q)
    {
        auto try_push = [&grid, &q](int x, int y) -> void {
            if ((x >= 0 && y >= 0) && (x < grid[0].size() && y < grid.size()) && grid[y][x] == '1')
            {
                grid[y][x] = VISITED;
                q.push(Point{.x = x, .y = y});
            }
        };

        try_push(pt.x, pt.y - 1);
        try_push(pt.x, pt.y + 1);
        try_push(pt.x + 1, pt.y);
        try_push(pt.x - 1, pt.y);
    }
};
