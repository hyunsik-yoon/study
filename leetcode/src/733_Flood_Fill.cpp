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

// 733_Flood_Fill

// https://leetcode.com/problems/flood-fill/description/

class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color)
    {
        auto original_color = image[sr][sc];
        auto target_color = color;

        if (original_color != target_color)
        {
            // floodFill_recursive(image, sr, sc, original_color, target_color);
            floodFill_iterative(image, sr, sc, original_color, target_color);
        }

        return image;
    }

    void floodFill_recursive(vector<vector<int>>& image, int sr, int sc, int original_color, int target_color)
    {
        if (image[sr][sc] != original_color)
            return;
        if (image[sr][sc] == original_color)
        {
            image[sr][sc] = target_color;

            if (0 <= sc - 1) floodFill_recursive(image, sr, sc - 1, original_color, target_color);
            if (sc + 1 < image[0].size()) floodFill_recursive(image, sr, sc + 1, original_color, target_color);
            if (0 <= sr - 1) floodFill_recursive(image, sr - 1, sc, original_color, target_color);
            if (sr + 1 < image.size()) floodFill_recursive(image, sr + 1, sc, original_color, target_color);
        }
    }

    void floodFill_iterative(vector<vector<int>>& image, int sr, int sc, int original_color, int target_color)
    {
        struct Point
        {
            int r, c;
        };

        queue<Point> q;

        q.push(Point{sr, sc});

        while (! q.empty())
        {
            auto point = q.front();
            q.pop();
            image[point.r][point.c] = target_color;

            if (0 <= point.c - 1 && image[point.r][point.c - 1] == original_color)
                q.push(Point{point.r, point.c - 1});
            if (point.c + 1 < image[0].size()  && image[point.r][point.c + 1] == original_color)
                q.push(Point{point.r, point.c + 1});

            if (0 <= point.r - 1 && image[point.r - 1][point.c] == original_color)
                q.push(Point{point.r - 1, point.c});
            if (point.r + 1 < image.size()  && image[point.r + 1][point.c] == original_color)
                q.push(Point{point.r + 1, point.c});
        }
    }

};
