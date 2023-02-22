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

// 48_Rotate_Image

// https://leetcode.com/problems/rotate-image/description/

// REMEMBER
// - 코드가 너무 길어지면 이상한거다. 다시 생각하라.

class Solution {
public:
    void rotate(vector<vector<int>>& matrix)
    {
        int x_center = matrix.size() / 2;
        int last_idx = matrix.size() - 1;

        for (int layer = 0; layer < x_center; layer++)
        {
            // REMEMBER
            // 처음에 아래처럼 짰는데..... TC를 돌려보면 틀렸다는 것을 알 수 있었을 것이다.
            //     for (int k = 0; k < last_idx; k++)

            for (int k = 0; k < last_idx - 2*layer; k++)
            {
                int x0 = layer + k;
                int y0 = layer;
                int v0 = matrix[y0][x0];

                int x1 = last_idx - layer;
                int y1 = layer + k;
                int v1 = matrix[y1][x1];

                int x2 = last_idx - layer - k;
                int y2 = last_idx - layer;
                int v2 = matrix[y2][x2];

                int x3 = layer;
                int y3 = last_idx - layer - k;
                int v3 = matrix[y3][x3];
            }
        }
    }
};
