#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 349_Intersection_of_Two_Arrays

// https://leetcode.com/problems/intersection-of-two-arrays/solutions/

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
    {
        return intersection__3n__3n(nums1, nums2);
        // return intersection__builtin(nums1, nums2);
    }

    vector<int> intersection__3n__3n(vector<int>& nums1, vector<int>& nums2)
    {
        unordered_set<int> s1(nums1.begin(), nums1.end());
        unordered_set<int> s2(nums2.begin(), nums2.end());
        vector<int> ans;

        for (const auto num: s1)
            if (s2.count(num) > 0)
                ans.emplace_back(num);

        return ans;
    }

    vector<int> intersection__builtin(vector<int>& nums1, vector<int>& nums2)
    {
        vector<int> ans;

        // REMEMBER
        // std::set_intersection will return [2, 2]  ==> wrong answer for this question since answer should contain unique nums
        // if nums1 = [1, 2, 2, 3] and nums2 = [5, 2, 2]
        std::set_intersection(nums1.begin(), nums1.end(),
                              nums2.begin(), nums2.end(),
                              std::back_inserter(ans));

        return ans;
    }

    // sorting two then creating ans: 2nlogn + n, nlogn + n
};

/*
REMEMBER

Set is an ordered sequence of unique keys
whereas unordered_set is a set in which key can be stored in any order, so unordered.

Set is implemented as a balanced tree structure.
that is why it is possible to maintain order between the elements (by specific tree traversal).

The time complexity of set operations is O(log n) while for unordered_set, it is O(1).

From https://www.geeksforgeeks.org/unordered_set-in-cpp-stl/
*/
