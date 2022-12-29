#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/pascals-triangle/description/

class Solution {
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> ans;
        for (int r = 0; r < numRows; ++r)
        {
            add_row(r, ans);
        }

        return ans;
    }

private:
    void add_row(int nth_row, vector<vector<int>> &ans)
    {
        ans.emplace_back(vector<int>{});
        vector<int> &row = ans[nth_row];

        for (int k = 0; k <= nth_row; ++k)
        {
            int val;

            if (k == 0 || k == nth_row)
                val = 1;
            else
            {
                vector<int> &prev_row = ans[nth_row-1];
                val = prev_row[k-1] + prev_row[k];
            }

            row.emplace_back(val);
        }
    }
};
