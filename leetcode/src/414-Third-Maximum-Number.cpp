// For https://leetcode.com/problems/third-maximum-number

#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    int thirdMax(vector<int>& nums) {
        solve_1(nums);
    }

private:
    int solve_1(vector<int>& nums) {

        // TC
        // [1], [1, 2], [1, 1, 2], [1, 2, 3, 4]
        // [1, 2, -std::pow(2, 31)]

        auto max_1 = std::max_element(nums.begin(), nums.end()); // REMEMBER std::max_element

        std::set<int> maxes = { *max_1 };

        // retrun true if next_max is found
        // return false if next_max is not found
        auto find_next_max = [&nums, &maxes](int &next_max) {
            bool found = false;

            // REMEMBER std::pow() is in <cmath>. <cmath> is C++ header for <math.h>
            next_max = - std::pow(2, 31);
            for (auto num: nums)
            {
                if (maxes.find(num) != maxes.end())
                {
                    continue;
                }

                if (num >= next_max) // NOTE equal sign (">=") is needed since num can be -pow(2, 31)
                {
                    next_max = num;
                    found = true;
                }
            }
            return found;
        };

        int next_max;

        if (find_next_max(next_max))
        {
            maxes.emplace(next_max);
        }
        else
        {
            return *max_1;
        }

        if (find_next_max(next_max))
        {
            return next_max;
        }
        else
        {
            return *max_1;
        }
    }
};

// REMEMBER
// in https://leetcode.com/problems/third-maximum-number/solutions/2614958/third-maximum-number/
//
// 2) Min heap solution using
//    priority_queue<int, vector<int>, greater<int>> minHeap;
//
// 3) set<int> sortedNums;
//    where *sortedNums.begin() is the smallest number.
