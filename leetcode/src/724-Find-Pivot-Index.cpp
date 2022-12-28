// https://leetcode.com/problems/find-pivot-index/description/

// REMEMBER Calculate whole sum first

#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {

        // TC
        // [1 4 2 3 2], [-1 -4 3 2 -2]  -> pivot in the middle
        // [0], [2, 1, -1], [-1, -2, 3]  -> edge
        // [1], [1, 2, 3]   --> -1

        // 1. make left sum and right sum
        // 2. if left sum > right sum, proceed one more to the right sum

        int n = nums.size();

        int whole_sum = std::accumulate(nums.begin(), nums.end(), 0, [](int a, int b) { return a + b; });

        int left_sum = 0;
        for (int k = 0; k < nums.size(); k++)
        {
            if (left_sum == whole_sum - left_sum - nums[k])
                return k;

            left_sum += nums[k];
        }

        return -1;
    }
};

/*
REMEMBER
    My previous answer:
        - I used two maps, which seemed not very efficient when I solved this problem....

using IdxT = int;
using SumT = int;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {

        // TC
        // [1 4 2 3 2], [-1 -4 3 2 -2]  -> pivot in the middle
        // [0], [2, 1, -1], [-1, -2, 3]  -> edge
        // [1], [1, 2, 3]   --> -1

        // 1. make left sum and right sum
        // 2. if left sum > right sum, proceed one more to the right sum

        int n = nums.size();

        map<IdxT, SumT> left_sums, right_sums;

        int sum = 0;
        for (int k = 0; k < n; k++)
        {
            sum += nums[k];
            left_sums[k] = sum;
        }

        sum = 0;
        for (int k = n - 1; k >= 0; k--)
        {
            sum += nums[k];
            right_sums[k] = sum;
        }

        // check edge case
        if (n == 1)
            return 0;

        // left edge
        if (right_sums[1] == 0)
            return 0;

        // others
        for (int k = 1; k <= n - 2; k++)
            if (left_sums[k-1] == right_sums[k+1])
                return k;

        // right edge
        if (left_sums[n-2] == 0)
            return n - 1;

        return -1;
    }
};

*/
