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

// 362. Design Hit Counter
// https://leetcode.com/problems/design-hit-counter/description/

class HitCounter {
public:
    HitCounter() {

    }

    void hit(int timestamp) {
        ++records[timestamp];
    }

    int getHits(int timestamp) {
        auto it = std::lower_bound(records.begin(), records.end(), timestamp - 300 + 1, [](const pair<const int, int> &p, int lb) {
            return p.first < lb;
        });

        int total = 0;
        for (auto i = it; i != records.end(); ++i)
        {
            total += i->second;
        }

        return total;
    }

private:
    map<int,int> records;
};

/**
 * Your HitCounter object will be instantiated and called as such:
 * HitCounter* obj = new HitCounter();
 * obj->hit(timestamp);
 * int param_2 = obj->getHits(timestamp);
 */

/*
 1 1
 2 1
 3 2
 300 2
 301 1
*/

 //  2.147 * 10^9 is roughly max of 32 bit int
 // -2.147 * 10^9 is roughly min of 32 bit int

