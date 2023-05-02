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

// 1046_Last_Stone_Weight
// https://leetcode.com/problems/last-stone-weight/description/

class Solution {
public:
    int lastStoneWeight(vector<int>& stones)
    {

        auto compare = [](int a, int b) { return a < b; };
        priority_queue<int, vector<int>, decltype(compare)> mq(compare);

        for(auto k: stones)
            mq.push(k);

        while(!mq.empty())
        {
            auto h1 = mq.top();
            mq.pop();

            if (mq.empty())
                return h1;

            auto h2 = mq.top();
            mq.pop();

            auto diff = std::abs(h1 - h2);

            if (diff != 0)
                mq.push(diff);
        }

        return 0;
    }
};
