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

// 1009_Complement_of_Base_10_Integer

// https://leetcode.com/problems/complement-of-base-10-integer/editorial/

// 0b101 을 주면 0b010 으로 0->1, 1->0 으로 바꾸는 complement 를 리턴

// REMEMBER
// 이 문제의 함정(?)은 0b00101 을 주면 0b11010 이 아니고 0b00010 을 리턴해야 한다는 것과
// 0b000를 주면 0b001 을 리턴해야 한다는 것. ---> 문제에 명시는 안되어 있다. 그러나 base case 이므로
// 인터뷰중에는 이상한 낌새를 눈치채고 물어봐야 한다.

// 그리고 xor (^) 를 쓰면 다소 쉬워진다.

class Solution {
public:
    int bitwiseComplement(int n)
    {
        // return method_using_boolean_not(n);
        return method_using_xor(n);
    }

    int method_using_boolean_not(int n)
    {
        // REMEMBER
        //      basecase 실제 체크 잊지 말 것
        if (n == 0) return 1;

        int ans = 0;
        int nn = n;

        int mask = 0x80000000;
        bool start = false;

        for (int i = 0; i < 8*sizeof(int); i++)
        {
            int left_most_bit = (nn & mask) >> 31;

            nn = nn << 1;

            if (!start && left_most_bit == 1)
                start = true;

            ans = ans << 1;

            // REMEMBER
            //      x == 1  일때 ~x (bitwise not) 을 하면 0b1111...1110 이 된다.
            //      당연한건데, 자꾸 ~x 를 하면 0b000...0000 이 된다고 착각했다.
            //      0b001 을 0b000 으로 만들려면 bitwise not이 아니고 boolean not 을 쓰도록.
            ans = ans | (start ? !left_most_bit : left_most_bit);

        }

        return ans;
    }

    int method_using_xor(int n)
    {
        /*  REMEMBER

            x = 1
            1 ^ x = 0   (reverted)
            0 ^ x = 1   (reverted)

            x = 0
            1 ^ x = 1   (as-is)
            0 ^ x = 0   (as-is)
        */

        /*
            from 30th bit to 0th bit in n

            if the bit is the first i
                start inverting the bit
        */

        if (n == 0) return 1;

        bool inverting = false;
        for (int i = 30; i >= 0; i--)
        {
            int filter = 1 << i;
            int bit = filter & n;

            // REMEMBER
            // 위의 bit 은 뭐 이를테면 00100 이런 수가 된다. (한비트가 1로 바뀌든지 0이든지)
            // 한 비트가 1일 때, if(bit == 1) 이라고 착각하지 말고 if(bit ) 0) 으로 조건을 쓰도록 할 것.

            if (inverting == false && bit > 0)
                inverting = true;

            if (inverting)
                n = n ^ filter;
        }

        return n;
    }
};
