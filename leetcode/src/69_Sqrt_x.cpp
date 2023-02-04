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


// 69_Sqrt_x_

// https://leetcode.com/problems/sqrtx/description/
//
// a^2 <= x < (a+1)^2 인 a 를 찾는 문제

class Solution {
public:
    int mySqrt(int target)
    {
        // return sqrt_iterative(target);
        return sqrt_bit_recursive(target);
    }

    int sqrt_iterative(int target)
    {
        // REMEMBER
        //
        // 처음 코드는 아래처럼 했는데 target == 1 에서 에러
        // 경계값+1 정도까지는 (여기서는 2) 테스트 해볼 것
        //
        // if (0 <= target && target < 1) return 1;

        if (0 <= target && target < 2) return target;

        uint32_t left = 0;
        // REMEMBER
        //
        // binary search 로 풀기 위해..
        // 처음에는 right 을 x 의 최대값의 root 로 잡았는데
        // uint32_t right = pow(2, 16);   // 2^16 * 2^16 = 2^32 > 2^31 - 1
        //
        // 사실 target 보다 적당히 작은 수로 잡아주는게 낫다.
        uint32_t right = target / 2;

        while (left < right)
        {
            uint64_t mid = (left + right) / 2;

            uint64_t mid_mid = mid * mid;

            // When left == 0 && right == 1, mid - 1 is negative. We add code for this on the top.
            if ((mid - 1) * (mid - 1) <= target && target < mid_mid)
                return mid - 1;

            // mid +1 > max won't happen
            if (mid_mid <= target && target < (mid + 1) * (mid + 1))
                return mid;

            if (mid_mid < target)
                left = mid + 1;
            else // target < mid_mid
                right = mid - 1;
        }

        assert(left == right);

        return left;
    }

    //
    // REMEMBER
    //  fancy way of solving this
    //
    //  root(target)
    //      = 2 * root(target/4)
    //      =     root(target >> 2) << 1
    //
    int sqrt_bit_recursive(int target)
    {
        if (target < 2) return target;

        int left = sqrt_bit_recursive(target >> 2) << 1;
        int right = left + 1;
        return target < (long)right * right ? left : right;
    }
};
