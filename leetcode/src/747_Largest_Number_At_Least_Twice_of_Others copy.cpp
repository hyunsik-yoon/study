#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/largest-number-at-least-twice-of-others/description/

class Solution {
public:
    int dominantIndex(vector<int>& nums) {

        // TC
        // correct: [1, 2], [0, 3, 10]
        // -1 : [1, 1], [1, 2, 3, 4]

        // find max
        int max = -1, max_idx = -1;
        for (int k = 0; k < nums.size(); k++)
        {
            if (nums[k] > max)
            {
                max = nums[k];
                max_idx = k;
            }
        }

        // find second max
        int second_max = -1;
        for (auto num: nums)
        {
            if (max > num && num > second_max)
            {
                second_max = num;
            }
        }

        // REMEMBER When using (max / second_max >= 2), beware "divide by zero" error.
        return (max >= second_max * 2) ? max_idx : -1;
    }
};
