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

// 278_First_Bad_Version
//
// https://leetcode.com/problems/first-bad-version/solutions/
//
// git 이 fail나기 시작했다.
// git commit들 중 오류나는 첫 commit 을 찾아라

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n)
    {
        // TC
        //  1    1
        //  2    1
        // MAX   1
        // MAX-1 1

        // return solve1(n);
        return solve2(n);
    }

    int solve1(int n)
    {
        if (n == 1 && isBadVersion(1)) return 1;

        int left = 1;
        int right = n;

        while (left < right)
        {
            int mid = (static_cast<long>(left) + right) / 2;

            if (isBadVersion(mid))
            {
                if (isBadVersion(mid - 1) == false) return mid;

                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        assert (left == right);
        return left;
    }

    int solve2(int n)
    {
        if (n == 1 && isBadVersion(1)) return 1;

        int left = 1;
        int right = n;

        while (left < right)
        {
            int mid = (static_cast<long>(left) + right) / 2;

            // REMEMBER
            // 여기 if 처리가 위랑 다른 방식인데
            //
            // 일단 right = mid 임. 즉, mid 가 bad 이면 right 을 bad 로 계속 유지하겠다는 것.
            // 그럼 반씩 나누다보면 결국 제일 첫 left == right 인 경우는 제일 첫 bad 가 된다.
            if (isBadVersion(mid))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }

        assert (left == right);
        return left;
    }
};
