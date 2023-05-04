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

// 1188_Design_Bounded_Blocking_Queue

// https://leetcode.com/problems/design-bounded-blocking-queue/description/

/*
approach 1. one mutex, one condition var

issue case (when capacity == 1)
    thread 1. deque() --> goes into 'wait state' since q.size() == 0
    thread 2. enque() --> push q but switched before mtx.unlock
    thread 3. enque() --> locked since mtx is acquired by th.2
    thread 2. enque() --> mtx.unlock
    thread 3. enque() --> wait since q.size() == 1
    thread 2. enque() --> cv.notify_one() end exits enque(). cv.notify_one() wakes thread 3
    thread 3. enque() --> wait since q.size() == 1

    so thread 1 and 3 are wait state and never wakes up

approach 2. uses one mutex, two cond var (one for enque another deque) to solve issue in the above
*/

#if 0

// Approach 1. One conditional var

class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity): cap{capacity} {
    }

    void enqueue(int element)
    {
        std::unique_lock q_lock(q_mtx);

        // when full, block the caller thread
        cv.wait(q_lock, [this](){ return q.size() < cap; });

        q.push(element);

        q_lock.unlock();
        cv.notify_one();
    }

    int dequeue()
    {
        // when empty, block the caller thread
        std::unique_lock q_lock(q_mtx);
        cv.wait(q_lock, [this]() { return q.size() > 0; });

        int ret = q.front();
        q.pop();

        q_lock.unlock();
        cv.notify_one();

        return ret;
    }

    int size()
    {
        std::unique_lock q_lock(q_mtx);

        return q.size();
    }

private:
    queue<int> q;
    const int cap;

    std::mutex q_mtx;
    std::condition_variable cv;
};
#endif

// Approach 2. One conditional var

class BoundedBlockingQueue {
public:
    BoundedBlockingQueue(int capacity): cap{capacity} {
    }

    void enqueue(int element)
    {
        std::unique_lock q_lock(q_mtx);

        w_cv.wait(q_lock, [this](){ return q.size() < cap; });

        q.push(element);
        q_lock.unlock();

        // notify dequeue thread
        r_cv.notify_one();
    }

    int dequeue()
    {
        // when empty, block the caller thread
        std::unique_lock q_lock(q_mtx);

        int ret;
        r_cv.wait(q_lock, [this]() { return q.size() > 0; });

        ret = q.front();
        q.pop();

        q_lock.unlock();

        // notify enqueue thread
        w_cv.notify_one();

        return ret;
    }

    int size()
    {
        std::unique_lock q_lock(q_mtx);

        return q.size();
    }

private:
    queue<int> q;
    const int cap;

    std::mutex q_mtx;

    // read conditional var
    std::condition_variable r_cv;

    // write conditional var
    std::condition_variable w_cv;
};

