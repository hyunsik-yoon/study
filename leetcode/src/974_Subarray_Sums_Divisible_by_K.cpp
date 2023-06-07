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

// 974. Subarray Sums Divisible by K
// https://leetcode.com/problems/subarray-sums-divisible-by-k/description/

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        // calculate accumulate sum and reminder of k
        // create a map of <r,count>
        map<int,int> m;
        int sum = 0;
        for (int i = 0; i < nums.size(); ++i)
        {
            sum += nums[i];
            int r = sum % k;

            // remove regative reminder
            if (r < 0) r += k;

            ++m[r];
        }

        int sub_count = 0;
        for (auto &item: m)
        {
            int r = item.first;
            int r_count = item.second;
            if (r_count > 1)
            {
                sub_count += r_count*(r_count - 1) / 2;
            }

            // m[0] = 1 을 m 선언 다음에 하면 아래 if 를 없앨 수 있다.
            if (r == 0) // from index 0 (inclusive) to here
            {
                sub_count += r_count;
            }
        }

        return sub_count;
    }
};

/*
[5] 5
{0:1}

example 1)
reminder [5] 9
{5:1}

example 2)
[4,5,0,-2,-3,1]  k = 5
sum      [4 9 9 7 4 5]
reminder [4 4 4 2 4 0]

m {4:4, 2:1, 0:1}

for 4:4, 4*3/2 = 6
for 2, 0
for 0, 1
answer = 6+1

run example)
[-1,2,9] k = 2  answer should be [2], [-1, 2, 9]
sum [-1, 1, 10]
r   [-1, 1, 0]


run example)
[2,-2,2,-4] k = 6
s: [2 0 2 -2]
r: [2 0 2 -2]
m {2:2, 0:1, -2:1}
conut = 1 + 1 + 1 = 3

a = 6n - 2

b = 6m - 2
b = 6m + 4

run example)
[8,9,7,8,9] k = 8
s: [8 17 24 32 41]
r: [0  1  0  0  1]
m: {0:3, 1:2}
count = 3 + 1 + 3 = 7

--------------------

[-1 0 1 0] k = 2,       0,    0,  -1,0,1  -1,0,1,0,

[-1, -1, 1, 1]

[1 0 1 0] k = 2,       0,    0,  -1,0,1  -1,0,1,0,
[1 1 0 0]

4 ==> 6

3 2 1
1 2 3

4 4 4 / 2

0 0 0

2 1
1 2
3 3

[1 2 3] k =2
s: [1 3 6]
r: [1 1 0]



*/
