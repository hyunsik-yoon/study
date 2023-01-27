#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        rotate_O1(nums, k);
    }

    // space O(1)
    void rotate_O1(vector<int>& nums, int k)
    {
        // REMEMBER
        // [1, 2, 3, 4, 5] with k = 2  => answer: [4, 5, 1, 2, 3]
        //
        // 1. reverse : [5, 4, 3, 2, 1] will move shifting elements to left
        // 2. reverse front : [4, 5, 3, 2, 1]
        // 3. reverse back : [4, 5, 1, 2, 3]
        int N = nums.size();
        k = k % N;

        auto reverse = [](vector<int>& nums, int idx, int size)
        {
            // REMEMBER
            std::reverse(nums.begin() + idx, nums.begin() + idx + size);
        };

        reverse(nums, 0, nums.size());
        reverse(nums, 0, k);
        reverse(nums, k, nums.size() - k);
    }

    // space O(n)
    void rotate_ON(vector<int>& nums, int k) {
        int N = nums.size();

        k = k % N;

        vector<int> temp(k);

        // REMEMBER
        std::copy(nums.begin() + N - k, nums.end(), temp.begin());

        // REMEMBER usage of rbegin(). Do not decrease. (Not `it_src--`)
        for (auto it_src = nums.rbegin() + k, it_dst = nums.rbegin(); it_src < nums.rend(); it_src++, it_dst++)
        {
            *it_dst = *it_src;
        }

        // REMEMBER std::copy(src.begin(), src.end(), dst.begin());
        std::copy(temp.begin(), temp.end(), nums.begin());
    }
};

/*
REMEMBER
  std::reverse_copy

    std::vector<int> v({1,2,3});

    std::vector<int> destination(3);
    std::reverse_copy(std::begin(v), std::end(v), std::begin(destination));

    // now destination == {3, 2, 1}
*/

