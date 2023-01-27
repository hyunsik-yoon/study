#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

// https://leetcode.com/problems/add-binary/submissions/

// REMEMBER
//      Refer to approach 2 using binary operations (example in Java and Python which has very big integer)
//          https://leetcode.com/problems/add-binary/solutions/414426/add-binary/

class Solution {
public:
    string addBinary(string a, string b) {
        return solution_1(a, b);
        // return solution_2(a, b);
    }

    // shorter one
    string solution_2(string a, string b) {
        string &long_str = a.length() > b.length() ? a : b;
        string &short_str = a.length() <= b.length() ? a : b;

        int l = long_str.length() - 1;
        int s = short_str.length() - 1;

        vector<char> rev_ans;
        int carry = 0;

        while (l >= 0)
        {
            int val = carry;
            if (long_str[l] == '1') ++val;
            if (s >= l && short_str[l] == '1') ++val;

            /*
            REMEMBER

            or the following is also good (https://leetcode.com/problems/add-binary/solutions/24482/short-and-clear-code-in-c-bit-operation-from-full-adder/)

            (long_str[l] - '0') +
            (s >= l ? short_str[l] - '0' : 0) +
            carry
            */

            l--;

            // when val == 0, 2
            if (val % 2 == 0)
                rev_ans.emplace_back('0');
            else
                rev_ans.emplace_back('1');

            // when val == 2, 3
            carry = val / 2;
        }

        if (carry == 1)
            rev_ans.emplace_back('1');

        std::reverse(rev_ans.begin(), rev_ans.end());
        vector<char> &ans = rev_ans;

        return string(ans.begin(), ans.end());
    }

    // long solution
    string solution_1(string a, string b) {
        string &long_str = a.length() > b.length() ? a : b;
        string &short_str = a.length() <= b.length() ? a : b;

        vector<char> rev_ans;

        int l = long_str.length() - 1;
        int s = short_str.length() - 1;

        int carry = 0;
        while (s >= 0)
        {
            int val;
            if (long_str[l] == '0' && short_str[s] == '0') val = 0 + carry;
            else if (long_str[l] == '0' && short_str[s] == '1') val = 1 + carry;
            else if (long_str[l] == '1' && short_str[s] == '0') val = 1 + carry;
            else if (long_str[l] == '1' && short_str[s] == '1') val = 2 + carry;

            l--; s--;

            if (val == 0)
            {
                rev_ans.emplace_back('0');
                carry = 0;
            }
            else if (val == 1)
            {
                rev_ans.emplace_back('1');
                carry = 0;
            }
            else if (val == 2)
            {
                rev_ans.emplace_back('0');
                carry = 1;
            }
            else if (val == 3)
            {
                rev_ans.emplace_back('1');
                carry = 1;
            }
        }

        for (int k = l; k >= 0; k--)
        {
            int val;
            if (long_str[k] == '0') val = 0 + carry;
            else if (long_str[k] == '1') val = 1 + carry;

            if (val == 0)
            {
                rev_ans.emplace_back('0');
                carry = 0;
            }
            else if (val == 1)
            {
                rev_ans.emplace_back('1');
                carry = 0;
            }
            else if (val == 2)
            {
                rev_ans.emplace_back('0');
                carry = 1;
            }
        }

        if (carry == 1)
            rev_ans.emplace_back('1');

        std::reverse(rev_ans.begin(), rev_ans.end());
        vector<char> &ans = rev_ans;

        return string(ans.begin(), ans.end());
    }
};

// REMEMBER
//
// string to int
//      int val = std::stoi("123")
// int to string
//      string str = std::to_string(55)
//
// string to vector
//      string s(vec.begin(), vec.end());
// vector to string
//      vector v(str.begin(), str.end());
//
// reversing a vector
//      std::reverse(vec.begin(), vec.end())
