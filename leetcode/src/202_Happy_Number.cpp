#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 202_Happy_Number

// https://leetcode.com/problems/happy-number/submissions/

class Solution {
public:
    bool isHappy(int n)
    {
        unordered_set<int> done;

        while (true)
        {
            // decompose
            vector<int> v = decompose(n);

            // REMEMBER std::transform
            // map power
            std::transform(v.begin(), v.end(),  // from
                           v.begin(),           // into
                           [](int k) { return std::pow(k, 2); } );  // by applying

            // REMEMBER std::accumulate
            // add all
            int sum = std::accumulate(v.begin(), v.end(),  // from
                                     0,        // initial value to func
                                     [](int a, int b) { return a + b; });

            // if result is in 'done' return false ==> condition
            // if result is 1, finish
            if (sum == 1) return true;
            if (done.count(sum) > 0) return false;

            // put result into 'done'
            done.emplace(sum);
            n = sum;
        }

        throw std::runtime_error("Should not be here");
    }

    vector<int> decompose(int n)
    {
        // TC: 0, 5, 15
        vector<int> digits;
        for ( ; n > 0; n /= 10)
            digits.emplace_back(n % 10);

        return digits; // in reverse order
    }
};


/*
  REMEMBER

    // std::for_each 사용법

    auto print = [](const int& n) { std::cout << " " << n; };

    std::for_each(nums.cbegin(), nums.cend(), print);
*/

/*
  REMEMBER

    사실 decompose, transform, accumulate 를 한번에 하는게 효율적

    int get_happy_sum(int n)
    {
        // TC: 0, 5, 15
        int sum = 0;
        for ( ; n > 0; n /= 10)
            sum += std::pow(n % 10, 2);

        return sum;
    }

*/
