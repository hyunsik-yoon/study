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

// 1356_Sort_Integers_by_The_Number_of_1_Bits

// https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits/description/

struct BinInfo
{
    int val;
    int num_1bit;
};

// REMEMBER
// gcc has builtin function '__builtin_popcount(n)' which returns number of 1 bits in num
int get_1bit_count(int num)
{
    int count = 0;

    // REMEMBER
    //      loop 32 times --> NOT sizeof(int) BUT 8*sizeof(int) !!!!
    for (int i = 0; i < 8*sizeof(int); i++)
    {
        if ((num & 1) > 0) count++;
        num = num >> 1;
    }
    return count;

    // REMEMBER
    /*
    // another fancy way

    while (num != 0)
	{
		num = num & (num - 1);
        // (num - 1) will flip all bits up to and including the rightmost 1 in the binary representation of x.
        // by doing num & (num - 1), the right side of 1's will be removed
        // For example,
        // num is 010100, then num - 1 is 010011. num & (num - 1) = 010000
        // in next round, num is 010000, then num - 1 is 001111. num & (num - 1) = 000000
        // Beware the case when num == 0

		count++;
	}
    */
}

class Solution {
public:
    vector<int> sortByBits(vector<int>& arr)
    {
        // TC
        // [1]
        // [0,     1,2,      3]

        // make a vector of BinInfo
        vector<BinInfo> v;
        for (auto num: arr)
        {
            BinInfo bi;
            bi.val = num;
            bi.num_1bit = get_1bit_count(num);

            v.emplace_back(bi);
        }

        // sort by num_1bit and val
        auto asc_comp = [](const BinInfo &bi1, const BinInfo &bi2) {
            if (bi1.num_1bit < bi2.num_1bit) return true;
            if (bi1.num_1bit == bi2.num_1bit)
            {
                return (bi1.val < bi2.val);
            }

            // bi1.num_1bit > bi2.num_1bit
            return false;
        };

        std::sort(v.begin(), v.end(), asc_comp);

        for (int k = 0; k < v.size(); k++)
        {
            arr[k] = v[k].val;
        }

        return arr;
    }
};
