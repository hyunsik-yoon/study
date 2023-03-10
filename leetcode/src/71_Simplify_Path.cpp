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


// 71. Simplify Path

// https://leetcode.com/problems/simplify-path/description/

class Solution {
public:
    string simplifyPath(string path)
    {
        // return first_approach(path);
        return second_approach(path);
    }

    string second_approach(string &path)
    {
        deque<string> dq;
        string token{""};

        auto handle = [](deque<string> &dq, string &token)
        {
            if (token == "..")
            {
                if (!dq.empty()) dq.pop_back();
            }
            else if (token == ".")
                return;
            else if (token != "")
            {
                dq.push_back(token);
                token = "";
            }
            else throw runtime_error("token is empty");
        };

        for (int i = 0; i < path.length();)
        {
            if ((i + 1 < path.length()) && (path[i] == '/' && path[i+1] == '/'))
            {
                if (token != "") handle(dq, token);
                token = "";
                i = i + 2;
            }
            else if (path[i] == '/')
            {
                if (token != "") handle(dq, token);
                token = "";
                i++;
            }
            else
            {
                token += path[i];
                i++;
            }
        }

        if (token != "")
            handle(dq, token);

        // construct answer
        if (dq.empty()) return "/";

        string ans{};

        while (!dq.empty())
        {
            ans.append("/" + dq.front());
            dq.pop_front();
        }

        return ans;
    }


    string first_approach(string &path)
    {
        /*
        .  ..  //   traliling /     .. at root

        /a/b/c/../d

        */
        queue<string> q;

        string token{""};
        for (int i = 0; i < path.length();)
        {
            if ((i + 1 < path.length()) && (path[i] == '/' && path[i+1] == '/'))
            {
                if (token != "")
                {
                    q.push(token);
                    token = "";
                }
                i = i + 2;
            }
            else if (path[i] == '/')
            {
                if (token != "")
                {
                    q.push(token);
                    token = "";
                }
                i++;
            }
            else
            {
                token += path[i];
                i++;
            }
        }

        if (token != "")
            q.push(token);


        deque<string> dq;

        while (!q.empty())
        {
            string token = q.front();
            q.pop();

            if (token == "..")
            {
                if (!dq.empty()) dq.pop_back();
            }
            else if (token == ".")
                continue;
            else
                dq.push_back(token);
        }

        // construct answer
        if (dq.empty()) return "/";

        string ans{};

        while (!dq.empty())
        {
            ans.append("/" + dq.front());
            dq.pop_front();
        }

        return ans;
    }
};
