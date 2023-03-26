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

// ADD URL

class Solution {
public:
    bool validWordAbbreviation(string word, string abbr)
    {
        return method_1(word, abbr);
    }

private:
    bool method_1(string &word, string &abbr)
    {
        // TC
        // a, a,            aa
        // a, 1,            2, 1a, a1
        // abc, 2c, ab1     3c, 2cc, 2, a3, a2c

        int idx1 = 0;
        int idx2 = 0;

        while (idx1 < word.length() && idx2 < abbr.length())
        {
            if (islower(abbr[idx2]))
            {
                if (word[idx1] == abbr[idx2])
                {
                    idx1++;
                    idx2++;
                }
                else
                {
                    cout << word[idx1] << abbr[idx2] << endl;
                    return false;
                }
            }
            else // digit
            {
                auto get_numbers = [&abbr](int i) -> int {
                    int n = abbr[i] - '0';
                    if (n == 0) return -1;
                    if (i + 1 < abbr.length() && isdigit(abbr[i+1]))
                    {
                        n = n*10 + (abbr[i+1] - '0');

                        if (i + 2 < abbr.length() && isdigit(abbr[i+2])) return -1;
                    }

                    return n;
                };

                int nums = get_numbers(idx2);
                if (nums == -1) return false;

                idx1 += nums;
                idx2 += (nums < 10 ? 1 : 2);

            }
        }

        cout << (idx1 == word.length())  << (idx2 == abbr.length()) << endl;;
        return (idx1 == word.length() && idx2 == abbr.length());
    }
};

int main()
{
    std::cout << "start" << std::endl;

    Solution().validWordAbbreviation("internationalization", "i5a11o1");

    return 0;
}
