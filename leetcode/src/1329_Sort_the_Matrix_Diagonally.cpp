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

// 1329_Sort_the_Matrix_Diagonally

// https://leetcode.com/problems/sort-the-matrix-diagonally/submissions/

// 행렬을 각각 대각선들을 d 라고 할 때, d에 들은 요소들을 sort 하여 d에 다시 저장한 행렬를 리턴하라.

/*
REMEMBER

    1. matrix 에서 같은 diagnal 에 들어있는 elem 들은 아래같은 특성을 가지고 있음
        --> for elem mat[i, j] and mat[x, y], if i - k == x - y, mat[i, j] are mat[x, y] in the same diagnoal.
        이 문제에서 이 특성을 쓰는 방법이 있는데

            for each i, j:
                map의 key 를 i-j 로 하고 value 를 PQ로 한다.
                mat[i, j] 를 map[i-j]의 PQ에 저장
            for each i, j:
                mat[i, j] 를 map[i-j].pop() 해서 저장   <-- 정말 팬시하구나. 그러나 space complexity는 높다.

    2. vector 에 저장했다가 sort 를 하는 방법도 있는데
       그냥 PQ 에 넣었다가 pop 하는 방법도 있음. sort 를 명시적으로 부르지 않아도 됨.

    3. 문제에서 0 <= mat[i, y] <= 100 으로 100  정도이면 counting sort 를 쓰는 것이 나을 수 있음. (O(A+B), where A is mat 에서 저장하는 수의 갯수. B는 max - min)
*/

class DiagStart
{
public:
    DiagStart(vector<vector<int>>& mat)
    {
        max_x = mat[0].size();

        dsx = 0;
        dsy = mat.size() - 1;
    };

    bool move_next()
    {
        if (dsx > 0 && dsy > 0) throw runtime_error("Both cannot be postive.");

        if (dsx == max_x - 1) return false;

        if (dsx == 0 && dsy == 0) dsx = 1;
        else if (dsx == 0) dsy--;
        else if (dsy == 0) dsx++;

        return true;
    }

    int dsx;
    int dsy;

private:
    int max_x;
};

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat)
    {
        // TC
        // [[0]]

        if (mat.size() == 1 && mat[0].size() == 1) return mat;

        DiagStart ds(mat);
        vector<int> v(100);

        int max_y = mat.size();
        int max_x = mat[0].size();

        // for each diagnal line,
        //      copy value into v
        //      sort v
        //      store v into diagnal line

        do
        {
            int dsx = ds.dsx;
            int dsy = ds.dsy;

            // copy mat to v
            int vk = 0;
            int kx = dsx;
            int ky = dsy;
            for (; kx < max_x && ky < max_y; kx++, ky++, vk++)
            {
                v[vk] = mat[ky][kx];
            }

            // sort v
            std::sort(v.begin(), v.begin() + vk);

            // copy v to mat
            for (int kx = dsx, ky = dsy, vk = 0; kx < max_x && ky < max_y; kx++, ky++, vk++)
            {
                mat[ky][kx] = v[vk];
            }
        }
        while(ds.move_next());

        return mat;
    }
};
