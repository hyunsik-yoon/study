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

// 290. Word Pattern
// https://leetcode.com/problems/word-pattern/description/

class Token
{
public:
    Token(string &s): _s{s},  _start_idx{0} { }

    bool is_token_end()
    {
        return _start_idx == string::npos;
    }

    string next_token()
    {
        int next_space_index = _s.find(' ', _start_idx);

        // last token
        if (next_space_index == string::npos)
        {
            string ret(_s.begin() + _start_idx, _s.end());
            _start_idx = string::npos;
            return ret;
        }
        else
        {
            string ret(_s.begin() + _start_idx, _s.begin() + next_space_index);
            _start_idx = next_space_index + 1;
            return ret;
        }
    }

private:
    string _s;
    unsigned long _start_idx;
};

class Solution {
public:
    bool wordPattern(string pattern, string s)
    {
        // for each pattern char
        // if the pattern char is new one, store the char and word
        // if the pattern char was already shown, check if the same word was stored

        unordered_map<char, string> pm;
        unordered_set<string> tok_set;

        Token tok(s);

        for (int pi = 0; pi < pattern.length(); ++pi)
        {
            if (tok.is_token_end()) return false;

            auto found = pm.find(pattern[pi]);

            if (found == pm.end())
            {
                string token = tok.next_token();
                pm[pattern[pi]] = token;
                if (tok_set.count(token) > 0) return false;
                else tok_set.insert(token);
            }
            else
            {
                string token = tok.next_token();
                if (token != found->second) return false;
            }
        }

        if (!tok.is_token_end()) return false;

        return true;
    }
};
