#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/pascals-triangle-ii/description/

class Solution {
public:
    vector<int> getRow(int rowIndex) {
        // TC
        // 0 -> [1]
        // 1 -> [1, 1]
        // 2 -> [1, 2, 1]
        // 3 -> [1, 3, 3, 1]
        // 4 -> [1, 4, 6, 4, 1]
        return iterative_method_02(rowIndex);
    }

    // REMEMBER
    // With such pattern, think recusive way too!
    //
    // Recursive way may seem clean
    vector<int> recursive_method(int row_index) {
        if (row_index == 0)
            return {1};
        if (row_index == 1)
            return {1, 1};

        auto &&pv = recursive_method(row_index - 1);

        constexpr int init_val = 1;
        vector<int> v(row_index + 1, init_val);

        for (int i = 1; i < row_index; i++)
            v[i] = pv[i - 1] + pv[i];

        return v;
    }

    // Memory O(2N)
    vector<int> iterative_method_01(int rowIndex) {

        if (rowIndex == 0)
            return {1};
        if (rowIndex == 1)
            return {1, 1};

        // REMEMBER
        // Array creation with size 2
        std::array<std::vector<int>, 2> ans;

        // make answer from rowIndex = 2
        constexpr int init_val = 1;

        // REMEMBER resizing vector with initial value
        ans[0].resize(rowIndex + 1, init_val);
        ans[1].resize(rowIndex + 1, init_val);

        // REMEMBER Don't forget to return with reference!!!
        auto get_v = [&ans](int row_index) -> vector<int> & {
            auto idx = row_index % 2;
            return ans[idx];
        };

        for (auto row = 2; row <= rowIndex; row++)
        {
            // REMEMBER Don't forget to get the value with reference!!!
            auto &v = get_v(row);
            auto &pv = get_v(row - 1);

            v[0] = 1;
            v[row] = 1;

            for (int x = 1; x < row; x++)
            {
                v[x] = pv[x - 1] + pv[x];
            }
        }

        // REMEMBER
        // Check if this may create a new vector
        return get_v(rowIndex);
    }

    // REMEMBER this is also good to know (with only one vector)
    // Memory O(N)
    vector<int> iterative_method_02(int rowIndex) {
        if (rowIndex == 0)
            return {1};
        if (rowIndex == 1)
            return {1, 1};

        vector<int> v(rowIndex + 1, 1);

        // 1 -> [1, 1]
        // 2 -> [1, _2_, _1_]
        // 3 -> [1, 3,   _3_, 1]     ( _3_ = _2_ + _1_ )
        for (int row = 2; row <= rowIndex; row++)
            for (int i = row - 1; i >= 1; i--)
                v [i] = v[i - 1] + v[i];

        return v;
    }
};
