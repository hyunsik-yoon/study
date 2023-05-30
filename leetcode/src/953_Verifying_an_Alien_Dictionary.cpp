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

// 953. Verifying an Alien Dictionary
// https://leetcode.com/problems/verifying-an-alien-dictionary/description/

class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order)
    {
        map<char,int> order_map;
        for (int i = 0; i < order.length(); ++i)
            order_map[order[i]] = i;

        auto lexicograph_ok = [&order_map](string &s1, string &s2) -> bool {
            for (int i = 0; i < s1.length(); ++i)
            {
                int order1 = order_map[s1[i]];

                // what if s2.len() < s1.len() ?
                if (i < s2.length())
                {
                    int order2 = order_map[s2[i]];

                    if (order1 > order2) return false;
                    if (order1 < order2) return true;

                    // when order2 == order1, we don't know if it's ok yet
                }
                else // ["abc", "ab"]
                {
                    return false;
                }
            }
            // both are same
            return true;
        };

        for (int w = 0; w < words.size() - 1; ++w)
        {
            if (! lexicograph_ok(words[w], words[w+1])) return false;
        }

        return true;
    }
};
