#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 217_Contains_Duplicate

// https://leetcode.com/problems/contains-duplicate/description/

class Solution {
public:
    bool containsDuplicate(vector<int>& nums)
    {
        // REMEMBER
        //  unorder_set in <unorder_set>
        unordered_set<int> s(nums.begin(), nums.end());

        return nums.size() != s.size();
    }
};
