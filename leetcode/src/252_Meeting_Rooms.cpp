#include <algorithm>
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

// 252_Meeting_Rooms

// https://leetcode.com/problems/meeting-rooms/description/

// [미팅시작 t, 미팅끝 t]* 의 리스트를 주고 이 미팅시간이 overlap 이 되어 있는지를 파악하는 문제

class Solution {
public:
    bool canAttendMeetings(vector<vector<int>>& intervals)
    {
        // method 1.
        // sort by starting time
        // then check if
        //  for all i, end(i) <= start(i+1)
        //
        // time complexity: nlogn + n = nlogn
        // space complexity: 1

        // method 2.
        // prepare vector time. 0 means unassigned, 1 means assigned
        // for all i,
        //      for t in range(start(i), end(i))
        //          if time(t) == 1, return false;
        //
        // time complexity: 10^6
        // space complexity: 10^6  <== too much but let's try
        //
        // Actual result speed was, of course, generally not faster than method 1.

        return method_1(intervals);
        // return method_2(intervals);
    }

private:
    bool method_1(vector<vector<int>>& intervals)
    {
        if (intervals.size() == 0 || intervals.size() == 1) return true;

        auto compare_fn = [](const vector<int> &a, const vector<int> &b)
        {
            return (a[0] < b[0]);
        };

        std::sort(intervals.begin(), intervals.end(), compare_fn);

        // TODO
        for (int i = 1; i < intervals.size(); i++)
        {
            if (! (intervals[i-1][1] <= intervals[i][0]))
            {
                return false;
            }
        }

        return true;
    }

    bool method_2(vector<vector<int>>& intervals)
    {
        if (intervals.size() == 0 || intervals.size() == 1) return true;

        vector<bool> assigned(1000000, false);
        for (auto &interval: intervals)
        {
            int start = interval[0];
            int end = interval[1];

            for (int t = start; t < end; t++)
            {
                if (assigned[t] == true) return false;

                assigned[t] = true;
            }
        }

        return true;
    }
};
