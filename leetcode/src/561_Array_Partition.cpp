#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/array-partition/description/

class Solution {
public:
    int arrayPairSum(vector<int>& nums) {

        // REMEMBER Usage of std::sort to sort in ascending order
        std::sort(nums.begin(), nums.end(), [](int a, int b) { return a < b; });

        int sum = 0;

        for (int k = 0; k < nums.size(); k += 2)
        {
            sum += nums[k];
        }

        return sum;
    }
};
