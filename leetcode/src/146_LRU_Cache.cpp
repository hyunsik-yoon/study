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

// 146_LRU_Cache
// https://leetcode.com/problems/lru-cache/description/

using Key = int;
using Time = int;

class LRUCache {
private:
    unordered_map<Key,int> key_val;
    unordered_map<Key,Time> latest;
    queue<pair<Key,Time>> history;

    int capacity;
    Time t;

public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        t = 0;
    }

    int get(int key) {
        auto found = key_val.find(key);

        if (found == key_val.end())
            return -1;

        history.push(make_pair(key, t));
        latest[key] = t;
        ++t;

        return found->second;
    }

    void put(int key, int value) {
        // if key in key_value

        auto found = key_val.find(key);

        // already exist
        if (found != key_val.end())
        {
            found->second = value;
        }
        else
        {
            if (key_val.size() < capacity)
            {
                key_val[key] = value;
            }
            else
            {
                // when we need to remove old keys
                while (key_val.size() >= capacity)
                {
                    auto candidate = history.front();
                    history.pop();

                    if (candidate.second == latest[candidate.first])
                    {
                        // let's pop the least recently used key
                        key_val.erase(candidate.first);
                        latest.erase(candidate.first);
                        break;
                    }
                    // else case
                    // when latest usage of this key exists in a queue,
                    // let's just remove and check the next
                }

                // then let's store new key
                key_val[key] = value;
            }
        }

        history.push(make_pair(key, t));
        latest[key] = t;
        ++t;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
/*
   1 2 3 4 5
t1 0
t2   0
t3     0
t4       0
t5         0
t6 get(2)


[0, 10000]

  p p p p p g p p
t     3 4 5 6 7 8
k     3 4 5 1 3 6

*/
