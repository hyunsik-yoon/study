#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 136_Single_Number

// https://leetcode.com/problems/single-number/description/

class Solution {
public:
    int singleNumber(vector<int>& nums)
    {
        // runtime complexity should be O(n)
        // space complexity should be O(1)
        //
        // brute force O(n^2)
        // set space O(n)
        // sort O(nlogn), space O(nlogn)

        // REMEMBER
        //
        // Method 1.
        //  for
        //   k1, k2, k3, ... ki, kn
        //   k1, k2, k3, ...     kn
        //  calculate
        //   2*(all number) - 2(k1, k2, k3, ...   kn) + ki = ki
        //
        // Method 2.
        // XOR
        // -> a⊕0=a
        // -> a⊕a=0     same value --> 0
        // -> a⊕b⊕a=(a⊕a)⊕b=0⊕b=b

        int ans = 0;
        for (const auto &num : nums)
        {
            ans ^= num;
        }

        return ans;
    }
};
