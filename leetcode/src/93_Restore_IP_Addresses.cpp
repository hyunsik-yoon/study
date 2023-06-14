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

// 93. Restore IP Addresses
// https://leetcode.com/problems/restore-ip-addresses/description/

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> ans;

        try_dots(s, 0, 3, ans, "");

        return ans;
    }

    void try_dots(const string &s, int start, int dots, vector<string> &ans, string ip)
    {
        if (start >= s.length()) return;

        if (dots == 0)
        {
            if (start + 2 < s.length() - 1) return; // more than 3 digits

            string ip_part(s.begin() + start, s.end());
            int n = stoi(ip_part);
            if (n > 255) return;

            if (ip_part[0] == '0' && (ip_part.length() > 1)) return; // ip_num starts from '0'
            if (ip_part.length() > 2 && (ip_part[0] == '0' && ip_part[1] == '0')) return; // '00'

            ans.emplace_back(ip + ip_part);
        }

        // still having multiple dots

        // if '0', make it ip part
        if (s[start] == '0')
        {
            ip += '0';
            try_dots(s, start + 1, dots - 1, ans, ip + '.');
            return;
        }

        // if s[start] != '0'
        // 1. try one digit
        {
            ip += s[start];
            try_dots(s, start + 1, dots - 1, ans, ip + '.');
        }

        // 2. try two digits
        {
            if (start + 2 < s.length())
            {
                ip += s[start + 1];
                try_dots(s, start + 2, dots - 1, ans, ip + '.');
            }
        }

        // 3. try three digits
        {
            if (start + 3 < s.length())
            {
                int n = stoi(string(s.begin() + start, s.begin() + start + 3));
                if (n > 255) return;

                ip += s[start + 2];
                try_dots(s, start + 3, dots - 1, ans, ip + '.');
            }
        }
    }
};
/*
0279245587303
*/
