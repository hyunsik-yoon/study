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

// 926. Flip String to Monotone Increasing
// https://leetcode.com/problems/flip-string-to-monotone-increasing/description/

class Solution {
public:
    int minFlipsMonoIncr(string s)
    {
        // star k, meaning that all in [s[k], s.end) is 1
        //
        // n0 = check how many 1's after/from me?

        // count_0[i] means number of 0's in [i, end)

        int num_0 = 0;
        for (int k = s.size() - 1; k >= 0; --k)
        {
            if (s[k] == '0') ++num_0;
        }

        // check what if we change all 0's to 1's from s[k]
        int min_flip = s.size() + 1;

        int prev_flip_1_to_0 = 0;
        int flip_0_to_1 = num_0;

        for (int k = 0; k < s.size(); ++k)
        {
            int current_flip = prev_flip_1_to_0 + flip_0_to_1;

            min_flip = std::min(min_flip, current_flip);

            if (s[k] == '1') ++prev_flip_1_to_0;
            else --flip_0_to_1;
        }

        min_flip = std::min(min_flip, prev_flip_1_to_0);

        return min_flip;
    }
};
