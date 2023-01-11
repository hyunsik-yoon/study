#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

// 50_Pow

// https://leetcode.com/problems/powx-n/description/

class Solution {
public:
    double myPow(double x, int n) {
        // REMEMBER In case of recussion, do not call if call stacks are too many.
        // return pow_recursive(x, n);

        // REMEMBER In case of iteration, check if this requires too many iterations in the worst case.
        // return pow_iterative(x, n);

        // TC
        // 0, 0
        // 1, 10000
        // 2, 2^31-1
        // 1, -10000
        // 2, -(2^31)

        return pow_iterative(x, n);
    }


    double pow_performance(double x, int n)
    {
        // REMEMBER
        //
        //  음수도 되고 양수도 되는 경우를 잘 처리해야 한다.
        //  이것을 해결하려면 n 이 양수나 음수일때 모두를 가정한 코드를 만드는 것인데
        //          요것이 복잡하다. 예를 들어, for loop을 돌릴 때도 양수일 때는 for (int k = n; k > 1; k /= 2)
        //          가 되지만 음수는 k > 1 이라는 종료 조건이 이상해진다.
        //          또 % 연산자도 3 % 2 = 1 이지만
        //              -3 % 2 = -1 이어서 처리가 달라야 한다. (python 은 -3 % 2 is 1 이란다.)
        //  다른 방법은 n을 양수로 만들어주면 되는데,
        //          조건상 -2^31 <= n <= 2^31-1 이다
        //          n = -n 이라고 해버리면 n = -2^31 일때 -n 은 overflow error 가 난다.
        //  한가지 방법은 n = -2^31 경우를 특별히 처리하고
        //  나머지는 n = -n 으로 처리하는 방법이 있다.

        if (n == -pow(2, 31))
            return 1/x * pow_performance(1/x, -(n+1));

        if (n < 0)
        {
            x = 1/x;
            n = -n;
        }

        if (n == 0) return 1;
        if (n == 1) return x;
        if (n == -1) return 1/x;

        int half = n / 2;
        double val = pow_performance(x, half);

        // REMEMBER
        // In C, 3 % 2 returns 1. However, -3 % 2 is -1 and 3 % -2 gives 1.
        // In Python, -3 % 2 is 1 and 3 % -2 is -1.

        if (n % 2 == 1)
            return ( n >= 0 ? val * val * x : val * val * 1/x);
        else
            return val * val;
    }

    double pow_iterative(double x, int n)
    {
        if (n == -pow(2, 31))
            return 1/x * pow_performance(1/x, -(n+1));

        if (n < 0)
        {
            x = 1/x;
            n = -n;
        }

        // REMEMBER
        // 이부분이 잘 이해가 안됨

        double ans = 1;
        double current_product = x;
        for (long long i = n; i ; i /= 2) {
            if ((i % 2) == 1) {
                ans = ans * current_product;
            }

            current_product = current_product * current_product;
        }
        return ans;
    }

    double pow_recursive(double x, int n)
    {
        if (n == 0) return 1;

        if (n < 0)
            x = 1/x;

        return x * pow_recursive(x, n - 1);
    }
};
