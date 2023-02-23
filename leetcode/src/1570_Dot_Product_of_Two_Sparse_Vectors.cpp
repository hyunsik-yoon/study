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

// 1570_Dot_Product_of_Two_Sparse_Vectors

// https://leetcode.com/problems/dot-product-of-two-sparse-vectors/

class SparseVector {
public:

    SparseVector(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
            {
                m[i] = nums[i];
            }
        }
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec)
    {
        // TC
        // [0] [0]
        // [0] [1]
        // [1] [1]
        // [0 ... 1] [0 ... 1]

        int product = 0;
        for (const pair<int, int> &p: m)
        {
            int index = p.first;
            int value = p.second;

            if (vec.is_non_zero(index))
            {
                product += value * vec.get_val(index);
            }
        }

        return product;
    }

private:
    bool is_non_zero(int i)
    {
        return m.find(i) != m.end();
    }

    int get_val(int i)
    {
        // m[i] must exist
        return m[i];
    }

    unordered_map<int, int> m;
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
