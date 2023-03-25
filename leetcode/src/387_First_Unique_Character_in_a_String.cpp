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

// 387_First_Unique_Character_in_a_String

// https://leetcode.com/problems/first-unique-character-in-a-string/description/

class Solution {
public:
    int firstUniqChar(string s)
    {
        return method_1(s);
    }

    int method_1(string &s)
    {
        vector<int> index('z' - 'a' + 1, -1);
        vector<int> count('z' - 'a' + 1, 0);

        for (int k = 0; k < s.length(); k++)
        {
            int alpha_idx = static_cast<int>(s[k] - 'a');
            if (index[alpha_idx] == -1)
                index[alpha_idx] = k;
            ++count[alpha_idx];
        }

        int min_idx = s.length(); // largest
        for (int k = 0; k < 'z' - 'a' + 1; k++)
        {
            if (count[k] == 1)
            {
                if (min_idx > index[k])
                    min_idx = index[k];
            }
        }

        return (min_idx == s.length() ? -1 : min_idx);
    }
};

/*
"a"
"aba"

k = 2
idx = 0
       'a'     'b'
index   0       1
count   2       1

*/
