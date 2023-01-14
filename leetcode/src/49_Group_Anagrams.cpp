#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 49_Group_Anagrams
// https://leetcode.com/problems/group-anagrams/description/

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {

        auto get_base = [](string &word) -> string {
            string base = word;
            // REMEMBER
            std::sort(base.begin(), base.end());
            return base;
        };

        // for each string,
        //     convert it to base
        //     check if base is in map
        //     append string into map

        map<string, vector<string>> m;

        for (auto &str: strs)
        {
            auto base = get_base(str);

            auto found = m.find(base);
            if (found == m.end())
            {
                m[base] = {str};
            }
            else
            {
                // REMEMBER
                // 처음에 만들 떄 '&'를 빼먹어서 답의 vector size가 계속 1이었다.
                // 까먹지 말 것.
                auto &anagram_list = found->second;
                anagram_list.emplace_back(str);
            }
        }

        vector<vector<string>> ret;

        for (auto &pair : m)
            ret.emplace_back(pair.second);

        return ret;
    }
};
