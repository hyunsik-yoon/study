#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 359_Logger_Rate_Limiter

// https://leetcode.com/problems/logger-rate-limiter/description/1

class Logger {
public:
    Logger() {

    }

    bool shouldPrintMessage(int timestamp, string message)
    {
        // if msg is in disallowed and timestamp < disallowed.item.timestamp, return false
        // otherwise, update disapplowed

        auto found = disallowed.find(message);

        if (found != disallowed.end())
        {
            auto allowed_time = found->second;
            if (timestamp >= allowed_time)
            {
                int newly_allowed_timestamp = timestamp + 10;
                // update
                found->second = newly_allowed_timestamp;
                return true;
            }
            else
                return false;
        }
        else
        {
            disallowed[message] = timestamp + 10;
            return true;
        }
    }

private:
    map<string, int> disallowed;
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
