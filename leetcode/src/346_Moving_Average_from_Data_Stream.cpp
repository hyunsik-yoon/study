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

class MovingAverage_CircularArray {
public:
    MovingAverage_CircularArray(int size) : _v(size, 0), _size(size), _sum(0), _pos(0), count_called(0) { /* empty */ }

    double next(int val)
    {
        // REMEMBER
        //      DO Not use static because
        //      MovingAverage_CircularArray ma_1(); ma_1.next() ---> now count_called = 1
        //      MovingAverage_CircularArray ma_2(); ma_2.next() ---> now count_called = 2   !!!!
        // static int count_called = 0;

        count_called++;

        // REMEMBER
        // When circularArray is not full, _v[_pos] == 0
        _sum = _sum + val - _v[_pos];
        _v[_pos] = val;
        _pos = (_pos + 1) % _size;

        return (count_called <= _size) ? static_cast<double>(_sum) / count_called
                                       : static_cast<double>(_sum) / _size;
    }

private:
    vector<int> _v;
    int _size;
    int _sum;
    int _pos;      // after full, where to pop the value and where to put the next value?
    int count_called;      // now many times next() is called
};

class MovingAverage_Queue {
public:
    MovingAverage_Queue(int size) {
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
            // REMEMBER C++ queue
            //
            //  q.push(1); q.push(2); q.push(3);    // push 는 vector.emplace_back() 처럼 동작
            //
            //  q.front() is 1
            //  q.back()  is 3
            //  q.pop()   pops 1 (front)

            int old_val = _q.front();
            _q.pop();
            _q.push(val);

            _sum += val;
            _sum -= old_val;

            // REMEMBER
            //      Beaware of type
            //      To return double, don't forget type casting before int operation
            return static_cast<double>(_sum) / _size;
        }

        throw std::runtime_error("Should not be here");
    }

private:
    std::queue <int> _q;
    int _size;
    int _sum;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */

class MovingAverage : public MovingAverage_CircularArray {
// REMEMBER
//      1. Don't forget to add 'public'
//      2. Remember how to call parent's constructor
public:
    MovingAverage(int size) : MovingAverage_CircularArray(size) {  /* empty */ }
};

// class MovingAverage : public MovingAverage_Queue {
// public:
//     MovingAverage(int size) : MovingAverage_Queue(size) {  /* empty */ }
// };


// REMEMBER
//
// You can also use std::deque<int>      (not std::dequeue !!)
//
//  std::deque<int> dq;
//  dq.push_front(2);
//  dq.push_back(3);    // 2, 3
//  dq.push_front(1);   // 1, 2, 3
//  dq.push_back(4);    // 1, 2, 3, 4
//  int f = dq.front(); // 1
//  int b = dq.back();  // 4
//  dq.pop_front();     // 2, 3, 4
//  dq.pop_back();      // 2, 3
//
// see https://www.geeksforgeeks.org/deque-cpp-stl/
