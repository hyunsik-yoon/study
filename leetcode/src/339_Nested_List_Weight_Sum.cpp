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

// 339_Nested_List_Weight_Sum

// https://leetcode.com/problems/nested-list-weight-sum/description/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList)
    {
        // TC
        // [1] => 1
        // [1, 2] => 3
        // [ [1], [2] ] => 6
        // [ [1,1], 2, [1,1] ] => 10

        int total_sum = 0;
        calc_list(nestedList, 1, total_sum);

        return total_sum;
    }

private:
    void calc_list(vector<NestedInteger> &nestedList, int depth, int &total_sum)
    {
        for (int k = 0; k < nestedList.size(); k++)
        {
            NestedInteger &ni = nestedList[k];

            if (ni.isInteger())
            {
                total_sum += ni.getInteger() * depth;
                continue;
            }
            else
            {
                calc_list(nestedList[k].getList(), depth + 1, total_sum);
            }
        }
    }
};
