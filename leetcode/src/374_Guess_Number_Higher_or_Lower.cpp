#include <algorithm>
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

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

// 374_Guess_Number_Higher_or_Lower

// https://leetcode.com/problems/guess-number-higher-or-lower/description/
// 우리나라 숫자맞추기 업/다운 게임

#define HIGH   1
#define LOW    -1
#define EQU    0

class Solution {
public:
    int guessNumber(int n)
    {
        // TC
        // 1    1
        // 2    2
        // 3    2
        // max
        // max - 1

        return guess_binary_search(n);
    }
private:

    int guess_binary_search(int right)
    {
        int left = 1;

        while (left < right)
        {
            // REMEMBER
            //   INT_MAX is 2^31 - 1 (2,147,483,647)
            //   When one range of int is INT_MAX or INT_MIN, beware of the overflow with +, *
            //   Cast to long instead of int
            int mid = ((long)left + right) / 2;
            int g = guess(mid);

            switch (g)
            {
                case HIGH:
                    left = mid + 1;
                    break;
                case LOW:
                    right = mid - 1;
                    break;
                case EQU:
                    return mid;
            }
        }


        assert(left == right);

        return left;
    }
};
