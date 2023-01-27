#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/reverse-words-in-a-string/description/

struct Token
{
    int idx = -1;
    int len = -1;
};

class Solution {
public:
    string reverseWords(string s) {
        // TC
        // "   a   "
        // "a"
        // "aa"
        // "aa bb"
        return method_2(s);
    }

    // Method using token parsing
    string method_1(string &s)
    {
        // while scanning from the beginning, build tokens info list
        vector<Token> tokens;

        char prev_ch = ' ';
        int idx = -1, len = -1;

        for (int i = 0; i < s.length(); i++)
        {
            if (prev_ch == ' ' && s[i] != ' ')
            {
                idx = i;
            }
            else if (idx != -1 && s[i] == ' ')
            {
                len = i - idx;
                tokens.emplace_back(Token{idx, len});

                idx = len = -1;
            }

            prev_ch = s[i];
        }

        if (idx != -1)
            tokens.emplace_back(Token{idx, static_cast<int>(s.length() - idx)});

        // build vector<char> for return
        vector<char> v;

        for (int t = tokens.size() - 1; t >= 0; t--)
        {
            auto &tok = tokens[t];
            for (int i = 0; i < tok.len; i++)
                v.emplace_back(s[tok.idx + i]);

            if (t > 0)
                v.emplace_back(' ');
        }

        // return string
        return std::string(v.begin(), v.end());
    }

    // REMEMBER C++ string is like a vector. It is MUTABLE
    // using stdlib, such as string::find(), string::substr(), string::reserve(), string::append
    string method_2(string &s)
    {
        vector<string> tokens;

        int i = 0;
        while(true)
        {
            // REMEMBER string::find(substring, from_idx)
            int space_idx = s.find(" ", i);
            if (space_idx == i)
            {
                i++;
                continue;
            }
            // REMEMBER if (string::npos == string::find(substring, from_idx))
            else if (space_idx == string::npos)
            {
                if (s.length() - i != 0)
                    // REMEMBER, string::subst(idx, len)
                    tokens.emplace_back(s.substr(i, s.length() - i));
                break;
            }
            else
            {
                tokens.emplace_back(s.substr(i, space_idx - i));
                i = space_idx + 1;
            }
        }

        string res;

        int len = 0;
        for (auto & tok: tokens)
            len += tok.length() + 1 /* length for space */;
        len--; // for redundant space at the end of the loop

        // REMEMBER string::resize() makes len size string of spaces
        //          So, reserve() should be used
        // res.resize(len);
        res.reserve(len);

        for (int t = tokens.size() - 1; t > 0; t--)
        {
            // REMEMBER string::append(str)
            res.append(tokens[t]);
            res.append(" ");
        }
        res.append(tokens[0]);

        return res;
    }

};
