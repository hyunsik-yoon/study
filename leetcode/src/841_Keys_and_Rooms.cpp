#include <algorithm>
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

// 841_Keys_and_Rooms

// https://leetcode.com/problems/keys-and-rooms/description/

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        // main a set to denote which room we've visted
        // store room # into queue (if we didn't visited the room)
        // if queue empty and vsited.size() == rooms.size(), let's return true

        unordered_set<int> visited;
        queue<int> rooms_to_visit;

        // start from the room 0
        visited.emplace(0);
        for (int room: rooms[0])
            if (room != 0) rooms_to_visit.push(room);

        while (! rooms_to_visit.empty())
        {
            int next_room = rooms_to_visit.front();
            rooms_to_visit.pop();

            if (visited.count(next_room) > 0)
                continue;

            visited.emplace(next_room);

            for (int room: rooms[next_room])
                if (visited.count(room) == 0)
                    rooms_to_visit.push(room);
        }

        return (visited.size() == rooms.size());
    }
};
