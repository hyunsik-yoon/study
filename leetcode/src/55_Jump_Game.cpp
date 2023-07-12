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

// 55 jump game
// https://leetcode.com/problems/jump-game/description/?envType=study-plan-v2&envId=top-interview-150

#define NO_UNRESOLVED_ZERO -1

class Solution {
public:
    bool canJump(vector<int>& nums)
    {
        if (nums.size() == 1) return true;

        int zk = NO_UNRESOLVED_ZERO;
        for (int k = nums.size() - 1; k >= 0; --k)
        {
            if (zk != NO_UNRESOLVED_ZERO)
            {
                // found go over zero?
                if (zk == nums.size() -1 && zk - k <= nums[k])
                    zk = NO_UNRESOLVED_ZERO;
                else if (zk - k < nums[k])
                    zk = NO_UNRESOLVED_ZERO;
                else ;
            }
            else
            {
                if (nums[k] != 0) {
                    continue;
                }
                else
                {
                    zk = k;
                }
            }
        }

        if (zk != NO_UNRESOLVED_ZERO) return false;
        else return true;
    }
};
/*
3 2 3 2 2
T T T T T

0 1 2 3 4
2 0 2 1 0
    i   k
O(n)

from the end, find 0 at k
    from i <= k-1,
        if nums[i] == 0, then --i
        if k == nums.size() -1 && k - i <= nums[i], then ok
        if k - i < nums[i], then ok
*/
