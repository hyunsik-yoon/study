#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/longest-common-prefix/submissions/

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        // TC
        // { "" }
        // {"ab" }
        // {"", "ab" }
        // {"ab", "cd" }
        // { "ab", "abc" }

        return method_2(strs);
    }

    string method_2(vector<string>& strs)
    {
        // 1. find shortest string
        // 2. make a int vector v, v[k] means how many string matches the count
        //   1. count[k-1] > count[k] means that v[k] is not a part of longestCommonPrefix

        // Find shortest string, which will be used as potential LCP
        int min_idx = 0;
        for (int k = 0; k < strs.size(); k++)
        {
            if (strs[k].length() < strs[min_idx].length())
                min_idx = k;
        }

        const string &potential_LCP = strs[min_idx];
        if (potential_LCP.length() == 0) return "";

        // Initialize counts vector
        vector<int> counts(potential_LCP.length(), 0);

        // Increase count[k] when str[k] == potential_LCP[k]
        for (const string &str : strs)
        {
            if (str[0] != potential_LCP[0])
                return "";
            else
                counts[0]++;

            // REMEMBER Don't make mistake with && and ||   :-)
            for (int k = 1; k < str.length() && k < potential_LCP.length() ; k++)
            {
                if (counts[k-1] == counts[k] + 1 &&
                    str[k] == potential_LCP[k])
                    counts[k]++;
                else
                    break;
            }
        }

        // find the first counts[k], where counts[k] != strs.size()
        int lcp_idx = 0;
        // REMEMBER Don't make mistake with == and !=   :-)
        for ( /* empty */ ; lcp_idx < counts.size() && counts[lcp_idx] == strs.size(); lcp_idx++);

        // REMEMBER std::string.substr(index, length)
        // return real longestCommonPrefix
        return potential_LCP.substr(0, lcp_idx);
    }

    // This algorithm is [Approach 2: Vertical scanning] of official
    string method_1(vector<string>& strs)
    {
    // assume that strs[0] is a prefix..... then try to match strs[k] where k >= 1

        vector<char> prefix;
        bool match = true;

        for (int c = 0; c < strs[0].length(); c++)
        {
            char candidate = strs[0][c];

            for (int k = 1; k < strs.size(); k++)
            {
                if (c < strs[k].size() && strs[k][c] == candidate)
                {
                    match = true;
                }
                else
                {
                    match = false;
                    break;
                }
            }

            if (match)
                prefix.emplace_back(candidate);
            else
                break;
        }

        return string(prefix.begin(), prefix.end());
    }
};

int main()
{
    std::cout << "start" << std::endl;

    vector<string> input = {"flower","flow","flight"};
    std::cout << "\"" << Solution().longestCommonPrefix(input) << "\""
              << std::endl;
}
