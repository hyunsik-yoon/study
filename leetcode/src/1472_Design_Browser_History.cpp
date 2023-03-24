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

// 1472. Design Browser History

// https://leetcode.com/problems/design-browser-history/description/

class BrowserHistory {
public:
    BrowserHistory(string homepage) : current{0}, top{0}
    {
        history.emplace_back(homepage);
    }

    void visit(string url) {
        current++;

        if (current < history.size())
            history[current] = url;
        else
            history.emplace_back(url);

        top = current;
    }

    string back(int steps) {
        current = (current - steps >= 0 ? current - steps: 0);

        return history[current];
    }

    string forward(int steps) {
        current = (current + steps <= top ? current + steps : top);

        return history[current];
    }

private:
    vector<string> history;
    int current;
    int top;
};

/*
    0   1   2   3
    le  go  fa  li

v.size  4
current 0
forward 3

*/

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */
