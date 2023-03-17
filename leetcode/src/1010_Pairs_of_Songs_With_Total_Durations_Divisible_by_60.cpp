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
