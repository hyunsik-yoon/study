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

// 22. Generate Parentheses
// https://leetcode.com/problems/generate-parentheses/description/

#define OPEN '('
#define CLOSE ')'

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> ans;

        string generated;

        int available_open = n - 1;
        int closable_open = 1;

        string &s = generated.append(1, OPEN);

        attempt(n, s, available_open, closable_open, ans);

        return ans;
    }

    void attempt(const int n, string &generated, int available_open, int closable_open, vector<string> &ans)
    {
        if (generated.length() == 2*n)
        {
            ans.push_back(generated);
        }
        else
        {
            if (available_open > 0)
            {
                attempt(n, generated.append(1, OPEN), available_open - 1, closable_open + 1, ans);
                generated.pop_back();
            }

            if (closable_open > 0)
            {
                attempt(n, generated.append(1, CLOSE), available_open, closable_open - 1, ans);
                generated.pop_back();
            }
        }
    }
};
