// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array
// https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/solutions/2960418/c-o-1-space/

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

// REMEMBER There is a solution that change nums[i] to -1*nums[i] to indicate that nums[i] was found.

class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        // TC
        // normal       [1], [1, 2], [3,1,2]
        // duplication  [1, 1], [2, 2, 2]

        // let's use in-place operation
        //
        // for k, let's make nums[k] = FOUND, meaning that k'th index exists
        // then check nums[nums[]-1]

        constexpr int FOUND = -1;

        for (int k = 0; k < nums.size(); k++)
        {
            if (nums[k] == FOUND)
            {
                continue;
            }

            int j = nums[k] - 1;  // j means jump around starting from k
            while (nums[j] != FOUND)
            {
                int next_j = nums[j] - 1;
                nums[j] = FOUND;
                j = next_j;
            }
        }

        vector<int> res;
        for (int k = 0; k < nums.size(); k++)
        {
            if (nums[k] != FOUND)
                res.emplace_back(k + 1);
        }

        return res;
    }
};
