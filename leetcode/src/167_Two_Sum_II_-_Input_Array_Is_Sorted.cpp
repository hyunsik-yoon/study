#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/description/

// REMEMBER
//     don't forget condition, e.g. sorted input

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {

        int x = 0, y = numbers.size() - 1;

        while (true)
        {
            int sum = numbers[x] + numbers[y];
            if (sum == target)
                return {x+1, y+1};
            else if (sum < target)
                x++;
            else
                y--;
        }
        // REMEMBER
        throw std::runtime_error("should not be here");
    }
};
