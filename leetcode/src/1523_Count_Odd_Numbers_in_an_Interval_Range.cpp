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

// 1523_Count_Odd_Numbers_in_an_Interval_Range

// https://leetcode.com/problems/count-odd-numbers-in-an-interval-range/description/

// 주어진 두 수 사이에 존재하는 홀수의 갯수를 세는 문제

class Solution {
public:
    int countOdds(int low, int high)
    {
        // TC
        //  2, 2    O
        //  2, 3    O
        //  2, 4    O
        //  2, 5    O

        //  3, 3
        //  3, 4
        //  3, 5
        //  3, 6

        // return method_1(low, high);
        return method_2(low, high);
    }

    int method_2(int low, int high)
    {
        // REMEMBER
        // 짝수와 짝수 사이의 홀수를 세는데,
        // method_1 은 low + 1, high -1 로 바꾸어 계산했다. 이렇게 하면 원래 low, high 숫자 사이 숫자가 원래보다 줄어들어 복잡해진다.
        // method_2 은 low - 1, high -1 로 바꾸어 계산했다. 이렇게 하면 원래 low, high 숫자 사이 숫자가 원래보다 동일해서 계산이 간단하다.

        int count = 0;

        if (is_odd(low))
        {
            low = low - 1;
        }

        if (is_odd(high))
        {
            count++;
            high = high - 1;
        }
        return count + method_2_for_evens(low, high);
    }

    int method_2_for_evens(int el, int eh)
    {
        // 짝수로 만든 경우만 계산 (el: even low, eh: even high)
        assert(el % 2 == 0 && eh % 2 == 0);

        if (eh - el <= 0) return 0;
        else return (eh - el) / 2;
    }

    int method_1(int low, int high)
    {
        int count = 0;

        if (low == high)
        {
            if (is_odd(low)) return 1;
            else return 0;  // even
        }

        if (low + 1 == high) return 1;

        if (low + 2 == high)
        {
            if (is_even(low)) return 1;
            else return 2;
        }

        if (is_odd(low) )
        {
            count++;
            low = low + 1;
        }

        if (is_odd(high))
        {
            count++;
            high = high - 1;
        }

        count += (high - low) / 2;

        return count;
    }

private:
    bool is_odd(int x)
    {
        // REMEMBER
        // interesting way to implement x % 2 == 1
        return x & 1;
    }

    bool is_even(int x)
    {
        // REMEMBER
        // interesting way to implement x % 2 == 0
        return x | 0;
    }
};
