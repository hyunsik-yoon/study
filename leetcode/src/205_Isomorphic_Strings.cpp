#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 205_Isomorphic_Strings

// https://leetcode.com/problems/isomorphic-strings/description/

class Solution {
public:
    bool isIsomorphic(string s, string t)
    {
        // return solve_n_2n(s, t);
        return sovle_index_vector(s, t);
    }

    bool sovle_n_2n(string &s, string &t)
    {
        unordered_map<char, char> m;    // s -> t
        unordered_set<char> mapped_dst; // t의 집합. 또는 t -> s 의 map을 만들어도 됨.

        for (int k = 0; k < s.length(); k++)
        {
            char src_ch = s[k];
            char dst_ch = t[k];

            auto found = m.find(src_ch);

            if (found == m.end())
            {
                if (mapped_dst.count(dst_ch) > 0) return false;
                m[src_ch] = dst_ch;
                mapped_dst.emplace(dst_ch);
            }
            else
            {
                if (found->second != dst_ch)
                    return false;
            }
        }

        return true;
    }

    // REMEMBER 요런 방법도 있음
    bool sovle_index_vector(string &s, string &t)
    {
        // index 값을 vector 로 리턴. 2n
        auto to_index_vector = [](string &s)
        {
            using Index = int;
            map<char, Index> m;
            vector<Index> v;

            for (int k = 0; k < s.length(); k++)
            {
                auto found = m.find(s[k]);
                if (found != m.end())
                    v.emplace_back(found->second);
                else
                {
                    m[s[k]] = k;
                    v.emplace_back(k);
                }
            }

            return v;
        };

        auto v1 = to_index_vector(s);
        auto v2 = to_index_vector(t);

        // REMEMBER std::equal
        return std::equal(v1.begin(), v1.end(),
                          v2.begin());
    }
};
