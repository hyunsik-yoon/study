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

// 1268_Search_Suggestions_System
// https://leetcode.com/problems/search-suggestions-system/description/

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        sort(products.begin(), products.end());

        // find the first same prefix
        int left = 0;
        vector<vector<string>> ans(searchWord.size());
        for (int i = 0; i < searchWord.length(); ++i)
        {
            left = bin_search(products, left, products.size() - 1, searchWord, i, ans[i]);
            if (ans[i].size() == 0) break;
        }

        return ans;
    }

    int bin_search(vector<string> &products, int left, int right, string &w, int wk, vector<string> &ans)
    {
        /*
        p: [abc], wk = z
        l 0
        r -1
        m 0
        */
        auto compare = [](string &a, string &b, int end) {
            // -1: a[i-1] == b[i-1] but a[i] < b[i], for all 0 <= i <= end
            //  0: a[i] == b[i]
            //  1: a[i] > b[i]

            for (int i = 0; i <= end; ++i)
            {
                if (a[i] < b[i]) return -1;
                if (a[i] > b[i]) return +1;
            }
            return 0;
        };

        int mid = -1;
        bool found = false;
        while (left <= right)
        {
            mid = left + (right - left) / 2;

            if (compare(products[mid], w, wk) == -1)
            {
                left = mid + 1;
            }
            else if (compare(products[mid], w, wk) == +1)
            {
                right = mid - 1;
            }
            else
            {
                // we need to check if this is the first one that meets w[wk] == products[..][wk]
                // if not, let's move left
                if (left < mid && compare(products[mid - 1], w, wk) == 0)
                {
                        right = mid - 1;
                }
                else // products[mid][wk] is the first one
                {
                    found = true;
                    break;
                }
            }
        }

        if (found)
        {
            ans.emplace_back(products[mid]);

            for (int i = 1; i < 3; ++i)
            {
                if (mid + i < products.size() && compare(products[mid + i], w, wk) == 0)
                    ans.emplace_back(products[mid + i]);
            }

            return mid;
        }

        return 0;
    }
};
