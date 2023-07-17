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

// 6_Zigzag_Conversion
// https://leetcode.com/problems/zigzag-conversion/editorial/

class Solution {
public:
    string convert(string s, int numRows) {

        if (numRows == 1) return s;
        if (s.length() == 1) return s;

        string ans;

        for (int r = 0; r < numRows; ++r)
        {
            int intv1 = (r == numRows - 1 ? 0 : 2*((numRows - 1) - r  - 1) + 1);
            int intv2 = (r == 0? 0 : 2 *(r - 1) + 1);

            int src_ind = r;

            if (src_ind < s.length())
                ans.append(1, s[src_ind]);

            while (true)
            {
                if (r != numRows - 1) // intv1
                {
                    src_ind = src_ind + intv1 + 1;
                    if (!(src_ind < s.length())) break;

                    ans.append(1, s[src_ind]);
                }

                if (r != 0) // intv2
                {
                    src_ind = src_ind + intv2 + 1;
                    if (!(src_ind < s.length())) break;

                    ans.append(1, s[src_ind]);
                }
            }
        }

        return ans;
    }
};
/*
0123456689
paypalishiring
01210121012101

k *( 3+(r-2) )
0, 4, 8

k *( 3+(r-2) ) + 1
k *( 3+(r-2) ) + 2

01234456789012
PAYPALISHIRING
01232101232101

interval 1.
P     I     N      0 --> 3 -> 2 2 1
 A   L S  I  G     1 --> 2 --> 2 1
  Y A   H R        2 --> 1 --> 1
   P     I         3 --> 0

interval 2.
P     I     N       0 --> 0
 A   L S  I  G      1 --> 1
  Y A   H R         2 --> 2 + 1
   P     I          3 --> 2*2 + 1

0th row = 0 + (row + (row-2))k
1st row = 1 + (row + (row-2))k


*/
