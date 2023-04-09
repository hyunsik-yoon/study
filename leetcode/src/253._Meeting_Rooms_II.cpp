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

// 253._Meeting_Rooms_II

// https://leetcode.com/problems/meeting-rooms-ii/description/

// 미팅 시작, 종료 시간들의 목록들이 있을 때
// 미팅룸은 최대 몇개 있어야 하나?


/*
REMEMBER 풀이가 쉽지는 않다. 방을 관점으로 생각한다.

[0, 30], [0, 19], [10, 20], [25, 40], [30, 50]
                               +1        +1

1. sort meeting by staring time
2. 필요한 방을 heap에 저장하는데
3. remove the ending time(s) which is eariler than starting time of a new meeting
  -> 그래서 ending 타임을 저장하는 min heap 이 필요하고
  -> min heap 에 들어있는 수가 결국 미팅룸의 수가 된다.
*/

class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {

        std::sort(intervals.begin(), intervals.end(),
                  [](vector<int> &a, vector<int> &b) {
                      return a[0] < b[0];
                  });

        unsigned long max_count = 0;

        // REMEMBER
        //  std::priority_queue<int> heap 라고 선언하면 max heap 이 된다.
        //  min heap 을 위한 compare function 은 ">" 를 써야 함.
        //  sort 의 경우 ">" 을 쓰면 descending order 인데.
        //  descending order로 저장되어야 앞에서부터 작은수가 나온다... 뭐 이런식으로 외워라.

        auto compare = [](int a, int b) { return a > b; };

        std::priority_queue<int, vector<int>, decltype(compare)> min_heap(compare);

        for (auto &interval: intervals)
        {
            while (!min_heap.empty())
            {
                auto earliest = min_heap.top();
                if (earliest <= interval[0])
                    min_heap.pop();
                else
                    break;
            }

            min_heap.push(interval[1]);

            max_count = std::max(max_count, min_heap.size());
        }

        return static_cast<int>(max_count);
    }
};

/*
[0, 30], [0, 19], [10, 20], [25, 40], [30, 50]
                               +1        +1

1. sort meeting by staring time
2. remove the min ending time(s) which is eariler than new starting time
  -> min heap


[4,9],[4,17],[9,10]

[4,9]
[4,17]

*/

