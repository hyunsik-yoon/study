#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/diagonal-traverse/solutions/

// REMEMBER
// This is solution 2 in https://leetcode.com/problems/diagonal-traverse/solutions/459889/diagonal-traverse/
// Other solutions:
// - Solution 1 in https://leetcode.com/problems/diagonal-traverse/solutions/459889/diagonal-traverse/ seems
// - https://leetcode.com/problems/diagonal-traverse/solutions/459889/diagonal-traverse/comments/702348 is good to refer to.

struct Point
{
    Point(int x_, int  y_, bool up_): x{x_}, y{y_}, up{up_} { /* empty */ }

    int x, y;
    bool up;
};

class Strategy1
{
public:
    static vector<int> findDiagonalOrder(vector<vector<int>>& mat)
    {
        vector<int> res;

        int y_max = mat.size() - 1;
        int x_max = mat[0].size() - 1;

        Point start(0, 0, true);

        // REMEMBER check negative compound conditions again and again
        for (auto point = start; !(point.x == x_max && point.y == y_max); point = next(point, x_max, y_max))
        {
            res.emplace_back(mat[point.y][point.x]);
        }

        res.emplace_back(mat[y_max][x_max]);

        return res;
    }

    static Point next(const Point &last_point, int max_x, int max_y)
    {
        if (last_point.up)
        {
            // REMEBER Do not omit conditions that might not be needed.
            //         Try to make perfect conditions.
            //         Imperfect condition might end up with an unexpected runtime error.
            if (last_point.x < max_x && last_point.y == 0)
            {
                return Point(last_point.x + 1, 0, false);
            }
            else if (last_point.x == max_x)
            {
                return Point(max_x, last_point.y + 1, false);
            }
            else
            {
                return Point(last_point.x + 1, last_point.y - 1, true);
            }
        }
        else    // down
        {
            if (last_point.x == 0 && last_point.y < max_y)
            {
                return Point(0, last_point.y + 1, true);
            }
            else if (last_point.y == max_y)
            {
                return Point(last_point.x + 1, max_y, true);
            }
            else
            {
                return Point(last_point.x - 1, last_point.y + 1, false);
            }
        }
    }
};

class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& mat)
    {
        return Strategy1::findDiagonalOrder(mat);
    }
};
