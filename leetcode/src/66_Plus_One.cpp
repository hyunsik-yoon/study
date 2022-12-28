#include <algorithm>
#include <cmath>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/plus-one/description/

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        // TC
        // without carry: [1], [1, 2]
        // with carry: [9], [1, 9], [9, 9]

        auto &d = digits;
        bool carry = 1; // initially consider +1 to carry

        for (int k = d.size() - 1; k >= 0; k--)
        {
            // REMEMBER stop loop when no additional operation is necessary
            if (carry == 0)
                break;

            if (d[k] + carry < 10)
            {
                d[k] = d[k] + carry;
                carry = 0;
            }
            else
            {
                d[k] = 0;
                carry = 1;
            }
        }

        // REMEMBER vecter insertion
        if (carry == 1)
            d.insert(d.begin(), 1);

        return d;
    }
};
