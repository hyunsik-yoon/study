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

// 636_Exclusive_Time_of_Functions

// https://leetcode.com/problems/exclusive-time-of-functions/description/

class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs)
    {
        // when "start" push
        // when "end", pop "start", calculate exc
        //      exc[id] += end - start - child_exc
        //      and set child_exc of its parent to end - start

        using Time = int;
        using Child_exclusive_time = int;
        using Exclusive_time = int;

        vector<Exclusive_time> v(n, 0);

        stack<pair<Time, Child_exclusive_time>> call_stack;
        for (string &entry: logs)
        {
            int id = -1;
            string action = "";
            int time = -1;

            parse(entry, &id, &action, &time);

            if (action == "start")
            {
                call_stack.push(std::make_pair(time, 0));
            }
            else  // "end"
            {
                auto start_ctx = call_stack.top();
                call_stack.pop();

                int excution_time = time - start_ctx.first + 1;

                // calculate its exclusive time
                int exclusive_time = excution_time - start_ctx.second;
                v[id] += exclusive_time;

                // set parent's child_exclusive_time
                if (!call_stack.empty())
                {
                    auto &parent_start_ctx = call_stack.top();
                    parent_start_ctx.second += excution_time;
                }
            }
        }

        return v;
    }

private:
    void parse(const string &entry, int *id, string *action, int *time)
    {
        /*
        int idx1 = entry.find(":", 0);
        *id = stoi(string(entry.begin(), entry.begin() + idx1));

        int idx2 = entry.find(":", idx1 + 1);
        *action = string(entry.begin() + idx1 + 1, entry.begin() + idx2);

        *time = stoi(string(entry.begin() + idx2 + 1, entry.end()));
        */

        // REMEMBER
        //      use getline(input_stream, string_to_return, token='\n')
        //      use istringstream

        istringstream ss(entry);
        string temp;

        getline(ss, temp, ':');
        *id = stoi(temp);

        getline(ss, *action, ':');

        getline(ss, temp);
        *time = stoi(temp);
    }
};
