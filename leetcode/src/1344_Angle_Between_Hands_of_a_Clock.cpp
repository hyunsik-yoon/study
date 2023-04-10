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

// 1344_Angle_Between_Hands_of_a_Clock

// https://leetcode.com/problems/angle-between-hands-of-a-clock/description/

class Solution {
public:
    double angleClock(int hour, int minutes)
    {
        // hint: hour hand goes 1/(60*12) 'tick' when 1 minute passes
        // let's introduce normalized unit: tick
        // one circle has 60*12 == 720 ticks.

        // find hand with bigger angle in minute scale
        int hour_hand_tick = (hour % 12)*60 + minutes;
        int min_hand_tick = minutes * 12; // == (min / 60f) * (60 * 12);

        int tick_diff = std::abs(hour_hand_tick - min_hand_tick);
        if (tick_diff > 720 / 2) tick_diff = 720 - tick_diff;

        return  tick_diff / 2.0; // == tick_diff / (60 * 12) * 360;
    }
};

/* test case:

12:00
9:10

hour_hand_tick = 9*60 + 10 = 550
min_hand_tick = 120

720 - 430 => 290 / 2

*/
