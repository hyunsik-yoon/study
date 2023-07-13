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

// 1213_Intersection_of_Three_Sorted_Arrays

// https://leetcode.com/problems/intersection-of-three-sorted-arrays/description/

class Solution {
public:
    vector<int> arraysIntersection(vector<int>& a, vector<int>& b, vector<int>& c)
    {
        // return two_passes(a, b, c);
        return one_pass(a, b, c);
    }

private:
    vector<int> one_pass(vector<int>& a, vector<int>& b, vector<int>& c)
    {
        vector<int> res;

        int ak = 0, bk = 0, ck = 0;
        while (ak < a.size() && bk < b.size() && ck < c.size())
        {
            if (a[ak] == b[bk] && a[ak] == c[ck])
            {
                res.push_back(a[ak]);
                ++ak; ++bk; ++ck;
            }
            else
            {
                // REMEMBER
                //      3개를 비교하려니 복잡하다. 기준점 하나(아래 max처럼)를 잡고 비교한다.
                //      기준점이 된 아이(max 인 아이)도 비교를 당하는데 이정도 오버해드는 걍 눈감아줌
                int max = std::max(std::max(a[ak], b[bk]), c[ck]);
                while (ak < a.size() && a[ak] < max) ++ak;
                while (bk < b.size() && b[bk] < max) ++bk;
                while (ck < c.size() && c[ck] < max) ++ck;
            }
        }
        return res;
    }
    /*
    arr1 = [1,2,3,4,5],
                      ^
    arr2 = [1,2,5,7,9],
                  ^
    arr3 = [1,3,4,5,8]
                    ^

    res = [1,5]
    */

    vector<int> two_passes(vector<int>& a, vector<int>& b, vector<int>& c)
    {
        auto intersect = get_intersect(a, b);
        return get_intersect(intersect, c);
    }

    vector<int> get_intersect(vector<int>& a, vector<int>& b)
    {
        vector<int> res;

        int ak = 0, bk = 0;
        while (ak < a.size() && bk < b.size())
        {
            if (a[ak] == b[bk])
            {
                res.push_back(a[ak]);
                ++ak; ++bk;
            }
            else if (a[ak] < b[bk])
            {
                ++ak;
            }
            else // a[ak] > b[bk]
            {
                ++bk;
            }
        }
        return res;
    }
};
/*
arr1 = [1,2,3,4,5],
                  ^
arr2 = [1,2,5,7,9],
              ^

res =  [1,2,5]
              ^
arr3 = [1,3,4,5,8]
                ^

res = [1,5]
*/
