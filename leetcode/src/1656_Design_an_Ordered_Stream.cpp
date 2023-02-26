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

// 1656_Design_an_Ordered_Stream

// https://leetcode.com/problems/design-an-ordered-stream/solutions/

class OrderedStream {
public:
    OrderedStream(int sz) : buf(sz, ""), from{0}
    {
        // empty
    }

    vector<string> insert(int idKey, string value)
    {
        buf[idKey - 1] = value;
        if (buf[from] == "") return {};

        int s_idx = from;
        int e_idx = buf.size();
        for (int k = s_idx + 1; k < buf.size(); k++)
        {
            if (buf[k] == "") {
                e_idx = k;
                from = k;
                break;
            }
        }

        vector<string> ret(e_idx - s_idx);
        std::copy(buf.begin() + s_idx, buf.begin() + e_idx, ret.begin());

        return ret;
    }

private:
    vector<string> buf;
    int from;
};

/**
 * Your OrderedStream object will be instantiated and called as such:
 * OrderedStream* obj = new OrderedStream(n);
 * vector<string> param_1 = obj->insert(idKey,value);
 */
