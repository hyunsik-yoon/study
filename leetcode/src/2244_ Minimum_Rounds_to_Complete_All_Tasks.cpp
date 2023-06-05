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

// 2244. Minimum Rounds to Complete All Tasks
// https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/description/

class Solution {
public:
    int minimumRounds(vector<int>& tasks) {
        unordered_map<int,int> occurences;

        for (auto val: tasks)
            ++occurences[val];

        int round = 0;
        for (auto pr: occurences)
        {
            int occurence = pr.second;
            if (occurence == 1) return -1;
            else if (occurence == 2)
            {
                round += 1;
                continue;
            }
            else // occurence / 3 > 0
            {
                int count_3 = occurence / 3;
                int rest_3 = occurence % 3;

                if (rest_3 == 0) round += count_3;
                else if (rest_3 == 2) round += (count_3 + 1);
                else  // rest_3 == 1
                {
                    round += (count_3 - 1) + 2;
                }
            }
        }
        return round;
    }
};

/*
occurence
1  2   3 4 5 6 7
-1 1   1 2 2 2 (3,2,2)

task = [2,2,3,3,2,4,4,4,4,4]

{2:3, 3:2, 4:5}

1+1+2

*/
