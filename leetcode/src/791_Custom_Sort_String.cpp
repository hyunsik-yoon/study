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

// 791_Custom_Sort_String

// https://leetcode.com/problems/custom-sort-string/description/

class Solution {
public:
    string customSortString(string order, string s) {

        vector<int> alpha_order('z' - 'a' + 1, -1);

        for (int k = 0; k < order.length(); k++)
            alpha_order[order[k]-'a'] = k;

        auto do_sort = [&alpha_order](char ch1, char ch2)  {
            return alpha_order[ch1-'a'] < alpha_order[ch2-'a'];
        };

        std::sort(s.begin(), s.end(), do_sort);

        return s;
    }
};
