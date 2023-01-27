#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 249_Group_Shifted_Strings

// https://leetcode.com/problems/group-shifted-strings/description/

using StringV = vector<string>;

class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings)
    {
        // make base string where base[0] is always 'a'
        auto get_base = [](const string &s) -> string {
            vector<char> base(s.length());

            int delta_to_a = s[0] - 'a';
            for (int k = 0; k < s.length(); k++)
            {
                int candidate = s[k] - delta_to_a;
                // REMEMBER
                // number of alphabet is 26
                // 'char' type range is [0, 127]

                /* REMEMBER

                circular 한 경우의 처리를 해야 하는데("ba", "az" 이 같은 그룹이라고 함...)

                처음 코드

                base[k] = candidate >= 'a' ? candidate
                                           : 'z' - (delta_to_a - (s[k] - 'a')) + 1;

                아래는 좀 더 fancy한 solution code
                */
                base[k] = 'a' + (s[k] - delta_to_a + 26) % 26 ;        // 26을 더하고 %26 을 한다.
            }

            string ret = string(base.begin(), base.end());
            return ret;
        };

        map<string, StringV> m;

        for (const string &s: strings)
        {
            string base = get_base(s);
            auto found = m.find(base);

            if (found == m.end())
            {
                m[base] = {s};
            }
            else
            {
                auto & string_v = found->second;
                string_v.emplace_back(s);
            }
        }

        // return value
        vector<StringV> ans;
        for (auto &pair: m)
            ans.emplace_back(pair.second);
        return ans;
    }
};
