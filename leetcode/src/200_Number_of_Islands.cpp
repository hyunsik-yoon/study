// 200_Number_of_Islands

// https://leetcode.com/problems/number-of-islands/description/

// REMEMBER
//      an island in a 2x2 board can be considered as a graph

struct Point
{
    int km = -1;
    int kn = -1;
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        // 0 means water
        // 1 means land (not visited)
        // 2 means land (visited)

        auto should_visit = [&grid](const Point &p) {
            return grid[p.km][p.kn] == '1';
        };

        auto set_visited = [&grid](const Point &p) {
            assert(grid[p.km][p.kn] == '1');
            grid[p.km][p.kn] = '2';
        };

        int m = grid.size();
        int n = grid[0].size();

        int count = 0;

        for (int km = 0; km < m; km++)
        {
            for (int kn = 0; kn < n; kn++)
            {
                if (! should_visit(Point{km, kn})) continue;

                // start of new land
                count++;

                queue<Point> q;
                Point start{km, kn};
                set_visited(start);
                q.push(start);

                while (! q.empty())
                {
                    Point root = q.front();
                    q.pop();

                    auto try_push = [&grid, &should_visit, &set_visited](queue<Point> &q, Point &p)
                    {
                        if (should_visit(p)) {
                            set_visited(p);
                            q.push(p);
                        }
                    };

                    if (root.km != 0) {
                        Point up{root.km - 1, root.kn};
                        try_push(q, up);
                    }
                    if (root.km != m - 1) {
                        Point down{root.km + 1, root.kn};
                        try_push(q, down);
                    }
                    if (root.kn != 0)
                    {
                        Point left{root.km, root.kn - 1};
                        try_push(q, left);
                    }
                    if (root.kn != n - 1)
                    {
                        Point right{root.km, root.kn + 1};
                        try_push(q, right);
                    }
                }
            }
        }

        return count;
    }
};
