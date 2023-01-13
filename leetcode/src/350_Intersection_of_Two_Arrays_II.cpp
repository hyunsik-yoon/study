#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 350_Intersection_of_Two_Arrays_II

// https://leetcode.com/problems/intersection-of-two-arrays-ii/description/

class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
    {
        // TC
        // [1], [2] -> []
        // [2. 1], [3] -> []
        // [2. 1], [1] -> [1]
        // [2, 2, 3], [5, 2, 2, 3, 3] -> [2, 2, 3]

        using Count = int;

        map<int, Count> num1_m;

        for (auto num : nums1)
        {
            auto found = num1_m.find(num);

            if (found == num1_m.end())
                num1_m[num] = 1;
            else
                (found->second)++;
        }

        vector<int> ans;
        for (auto num: nums2)
        {
            auto found = num1_m.find(num);

            if (found == num1_m.end()) continue;
            else
            {
                if (found->second > 0)
                {
                    ans.emplace_back(num);
                    (found->second)--;
                }
            }
        }

        return ans;
    }
};
