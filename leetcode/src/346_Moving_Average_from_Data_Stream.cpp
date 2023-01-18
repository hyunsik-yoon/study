#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 346_Moving_Average_from_Data_Stream

// https://leetcode.com/problems/moving-average-from-data-stream/description/

class MovingAverage {
public:
    MovingAverage(int size) {
        _size = size;
        _sum = 0;
    }

    double next(int val) {
        if (_q.size() < _size)
        {
            _sum += val;
            _q.push(val);

            return static_cast<double>(_sum) / _q.size();
        }
        else if (_q.size() == _size)
        {
            int old_val = _q.front();
            _q.pop();
            _q.push(val);

            _sum += val;
            _sum -= old_val;

            return static_cast<double>(_sum) / _size;
        }

        throw std::runtime_error("Should not be here");
    }

private:
    std::queue <int> _q;
    int _size;
    int _sum;
};
