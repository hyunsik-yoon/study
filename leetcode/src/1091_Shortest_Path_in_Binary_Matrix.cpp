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

// 1091_Shortest_Path_in_Binary_Matrix

// https://leetcode.com/problems/shortest-path-in-binary-matrix/description/

#define NO_WAY 100*100

class Solution {
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid)
    {
        /*
        // TC
        // [[0]]

        // [[0,0,1,1,0,0]
            [0,0,0,0,1,1]
            [1,0,1,1,0,0]
            [0,0,1,1,0,0]
            [0,0,0,0,0,0]
            [0,0,1,0,0,0]]
        */

        if (grid[0][0] == 1) return -1;
        if (grid.size() == 1 && grid[0][0] == 0) return 1;

        // return method_backtrack(grid);
        return method_bfs(grid);
    }

    int method_bfs(vector<vector<int>>& grid)
    {
        grid[0][0] = 1;

        int N  = grid.size();

        queue<pair<int,int>> q;
        q.push({0,0});

        while (!q.empty())
        {
            auto coor = q.front();
            q.pop();

            auto count_coor = grid[coor.second][coor.first];

            if (coor.first == N-1 && coor.second == N-1)
                return count_coor;

            for (int kx = 1; kx >= -1; kx--)
            {
                for (int ky = 1; ky >= -1; ky--)
                {
                    if (kx == 0 && ky == 0) continue;

                    int next_x = coor.first + kx;
                    int next_y = coor.second + ky;

                    // boundary check
                    if (next_x >= grid[0].size() || next_y >= grid.size()) continue;
                    if (next_x < 0 || next_y < 0) continue;

                    int count_next_coor = grid[next_y][next_x];
                    if (count_next_coor == 1) continue;

                    if (count_next_coor == 0)
                    {
                        grid[next_y][next_x] = count_coor + 1;
                        q.push({next_x, next_y});
                    }
                }
            }
        }

        return -1;
    }

    int method_backtrack(vector<vector<int>>& grid)
    {
        int x = 0;
        int y = 0;
        set<pair<int,int>> visited{{0,0}};  // not sure yet

        int ans = backtrack(grid, 0, 0, visited);
        return (ans == NO_WAY ? -1 : ans);
    }

    int backtrack(vector<vector<int>>& grid, int x, int y, set<pair<int,int>> &visited)
    {
        /*
        backtracking 의 문제점은

        0 0 0
        0 0 0
        0 0 0

        이 있다면, [1,1] 에 도달하는 방법이 매우 많은데, 사실 그 중 최소값을 가지는 경로만 의미가 있는데
        그것보다 큰 이전 경로도 모두 유의미하게 보고 이후 경로를 살핀다는 것이다.
        그럼 [1,1] 에 이르는 최소값을 어떻게 아나? 예를 들어
        첫 탐색경로로... [0,0] -> [1,0] -> [1,1] 로 가서 3이 되고 [1,1] 후의 경로들도 다 탐색.. 끝까지 다 해보고,
        그 다음에 다시 시작해서 [0,0] -> [1,1] 로 가서 2가 되고... 이 경우는 사실 앞의 탐색은 다 무쓸모.
        따라서 [1,1]에서 시작하는 입장에서는 자기까지 대체 최소 경로는 얼마인가? 를 먼저 알아야 한다.
        DFS로 하면 아무래도 끝까지 한번 다 가봐야 하는지라, 이런게 좀 어렵다.
        */
        if (x == grid[0].size() - 1 && y == grid.size() - 1)
            return 1;

        int shortest = NO_WAY;
        for (int kx = 1; kx >= -1; kx--)
        {
            for (int ky = 1; ky >= -1; ky--)
            {
                if (kx == 0 && ky == 0) continue;

                int next_x = x + kx;
                int next_y = y + ky;

                if (next_x >= grid[0].size() || next_y >= grid.size()) continue;
                if (next_x < 0 || next_y < 0) continue;

                if (grid[next_y][next_x] != 0)
                {
                    continue;
                }
                if (visited.count({next_x, next_y}) > 0) continue;

                visited.insert({next_x, next_y});

                int res = 1 + backtrack(grid, next_x, next_y, visited);
                if (res < shortest)
                    shortest = res;

                visited.erase({next_x, next_y});
            }
        }

        return shortest;
    }
};
