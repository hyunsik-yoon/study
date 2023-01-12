#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 599_Minimum_Index_Sum_of_Two_Lists

// https://leetcode.com/problems/minimum-index-sum-of-two-lists/description/

class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2)
    {
        using Index = int;
        map<string, Index> m1;

        for (auto k = 0; k < list1.size(); k++)
            m1[list1[k]] = k;

        constexpr int INITIAL = 10000;
        int least_index_sum = INITIAL;

        // find minimum
        for (int k = 0; k < list2.size(); k++)
        {
            auto found = m1.find(list2[k]);
            if (found != m1.end())
            {
                int idx1 = found->second;
                int idx2 = k;

                if (idx1 + idx2 < least_index_sum)
                    least_index_sum = idx1 + idx2;
            }

            // or we can keep modifying vector when we found least_index_sum
            // but it seems such vector operation could be expensive
        }

        if (least_index_sum == INITIAL) return vector<string>{};

        // construc return vector
        vector<string> ans;
        for (auto k = 0; k < list2.size(); k++)
        {
            auto found = m1.find(list2[k]);
            if (found != m1.end())
            {
                int idx1 = found->second;
                int idx2 = k;

                if (idx1 + idx2 == least_index_sum)
                    ans.emplace_back(list2[k]);
            }
        }

        return ans;
    }
};
