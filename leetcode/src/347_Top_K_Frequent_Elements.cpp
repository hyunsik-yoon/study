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

class Solution {
public:
    int numIslands(vector<vector<char>>& grid)
    {
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


int main()
{
    std::cout << "start" << std::endl;

    vector<vector<char>> inputs =
     {{'1','1','1','1','1','0','1','1','1','1'},
      {'1','0','1','0','1','1','1','1','1','1'},
      {'0','1','1','1','0','1','1','1','1','1'},
      {'1','1','0','1','1','0','0','0','0','1'},
      {'1','0','1','0','1','0','0','1','0','1'},
      {'1','0','0','1','1','1','0','1','0','0'},
      {'0','0','1','0','0','1','1','1','1','0'},
      {'1','0','1','1','1','0','0','1','1','1'},
      {'1','1','1','1','1','1','1','1','0','1'},
      {'1','0','1','1','1','1','1','1','1','0'}};

    std::cout << "final answer: ";

    std::cout << "[" << std::endl;
    // std::for_each(input.begin(), input.end(), [&](int val) {
    //     double moving_ave = ma.next(val);
    //     std::cout << moving_ave << "," ;
    // });

    cout << Solution().numIslands(inputs);

    std::cout << "]" << std::endl;
}
