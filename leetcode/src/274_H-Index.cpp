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

// 274. H-Index
// https://leetcode.com/problems/h-index/description/?envType=study-plan-v2&envId=top-interview-150

class Solution {
public:
    int hIndex(vector<int>& cit)
    {
        sort(cit.begin(), cit.end());

        for (int i = cit.size() - 1; i >= 0; --i)
        {
            if (cit[i] == cit.size() - i) return cit[i];
            else if (cit[i] < cit.size() - i) return cit.size() - i - 1;
        }

        return cit.size();
    }
};

/*

0 0 3 5

0 : 4

4 : 2


21 60
2

1 : 2
60: 1

0 1 4 5 6 -> size = 5

0 : 5
1 : 4
4 : 3
5 : 2
6 : 1

1 1 3

1 : 3
1 : 2
3 : 1

*/
