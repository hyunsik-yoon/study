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

// 367_Valid_Perfect_Square

// https://leetcode.com/problems/valid-perfect-square/description/

// num 이 어떤 자연수의 재곱이면 true, 자연수의 재곱이 아니라면 false를 리턴
// Easy 문제이지만, 매우 어렵다고 생각됨
// 아래 REMEMBER 처럼 이상한 조건이 발생

class Solution {
public:
    bool isPerfectSquare(int num)
    {
        if (num < 2) return num;

        uint64_t l = 2;
        uint64_t r = num / 2;

        while (l < r)
        {
            uint64_t m = (l + r) / 2;
            uint64_t m_sq = m * m;

            if (m_sq == num) return true;

            // REMEMBER
            //      r*r < num 일 수 도 있다.
            //      그 경우 l, r 크기 관계가 이상해짐 l < r 이 아닌 관계로 갈 수 있음
            else if (num < m_sq) r = m - 1;
            else /* m_sq < num */ l = m + 1;
        }

        // REMEMBER
        // l > r 로 빠져나오는 경우가 발생

        return (l == r) && (l*l == num);
    }
};
