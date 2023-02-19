#include <algorithm>
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

// 1207_Unique_Number_of_Occurrences

// https://leetcode.com/problems/unique-number-of-occurrences/description/

class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr)
    {
        // store occurence into map
        // then use set to check occurence

        using Occurence = int;
        unordered_map<int, Occurence> m;

        for (auto num: arr)
        {
            auto found = m.find(num);
            if (found == m.end())
            {
                m[num] = 0;
            }
            else
            {
                found->second++;
            }
        }

        unordered_set<Occurence> s;

        // REMEMBER 첫번째가 const 임
        for (pair<const int, Occurence> &item: m)
        {
            if (s.count(item.second) == 0)
            {
                // REMEMBER set 에 item 추가하기는 set.insert()
                s.insert(item.second);
            }
            else
            {
                return false;
            }
        }

        return true;
    }
};
