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

// 1010_Pairs_of_Songs_With_Total_Durations_Divisible_by_60

// https://leetcode.com/problems/pairs-of-songs-with-total-durations-divisible-by-60/editorial/

// 더하면 60의 배수가 되는 pair 들은 몇개가 존재하나?

class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time)
    {
        // TC - positive
        // [60] --> 0
        // [20, 50, 40, 40, 20, 40]   --> 6
        // [30, 20, 150, 100, 40]  -> 3
        // [60, 60, 60]

        int count = 0;
        unordered_map<int,int> reminder_count;
        for (auto t: time)
        {
            int reminder = t % 60;                 // [0, 59]
            int required = (60 - reminder) % 60;   // [0, 59]

            // REMEMBER
            //  변수의 scope을 유의하라.
            // 첨에는 required 같은 경우 % 60 을 안해주었다. 그런데 scope 이 [0, 59]여야 하는데,
            // reminder 가 0 인경우 60 - 0 = 60 이 되어 의도와는 다르게 scope을 벗어났다.

            auto found = reminder_count.find(required);
            if (found != reminder_count.end())
            {
                count += found->second;
            }

            reminder_count[reminder]++;
        }

        return count;
    }
};
