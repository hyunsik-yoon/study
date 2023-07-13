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

// 540_Single_Element_in_a_Sorted_Array
// https://leetcode.com/problems/single-element-in-a-sorted-array/description/
//
// sorted array nums 가 있을 때, 딱 한 element 빼고 모든 element는 2개씩 중복되어 있다.
// 이 single element를 찾아라. 단 log(n) time 안에 찾아라.


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums)
    {
        // return method_1(nums);
        return method_2(nums);
    }

    int method_2(vector<int>& nums)
    {
        if (nums.size() == 1) return nums[0];

        int l = 0;
        int r = nums.size() - 1;

        while (l < r)
        {
            int m = r + (l-r)/2;

            // let's always check from even index
            if (m % 2 == 1) // odd index?
                --m;

            if (nums[m] == nums[m+1])
            {
                l = m + 2;
            }
            else // different
            {
                r = m;
            }
        }
        assert(l == r);
        return nums[l];
    }


    int method_1(vector<int>& nums)
    {
        if (nums.size() == 1) return nums[0];

        int l = 0;
        int r = nums.size() - 1;

        while (l < r)
        {
            int m = r + (l-r)/2;

            // is the right ones (from m) from m has even count?
            if ((r - m + 1) % 2 == 0)
            {
                if (nums[m] == nums[m+1]) // right side does not have the one we're loking for
                {
                    r = m - 1;
                }
                else // right side has the one
                {
                    l = m;
                }
            }
            else // right side has odd count
            {
                if (nums[m-1] == nums[m]) // right side (from m-1) does not have the one we're loking for
                {
                    r = m;
                }
                else // left side has the one
                {
                    l = m;
                }
            }
        }
        assert(l == r);
        return nums[l];
    }
};

/*

0 1 2 3 4
1,1,2,3,3
        l      r
0 1 2 3 4   5  6
3,3,7,7,10,11,11

0 1 2 3 4 5 6 7 8
1 3 3 5 5 7 7 8 8

0 1 2 3 4 5 6
1 3 3 5 5 7 7

0 1 2 3 4 5 6
1 1 3 3 5 5 7

0 1 2 3 4 5 6
1 1 3 5 5 7 7

0 1 2 3 4 5 6
1 1 3 3 5 7 7
*/
