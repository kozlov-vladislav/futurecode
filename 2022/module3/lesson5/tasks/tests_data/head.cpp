#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <random>
#include <cassert>
#include <thread>
#include <mutex>
#include <ctime>
#include <future>


class Fork {
    std::mutex _mutex;
    int _number;
    std::atomic<int> _counter1 = 0;
    std::atomic<int> _counter2 = 0;
public:
    void SetNumber(int n) {
        _number = n;
    }
    Fork& operator=(const Fork&) = delete;
    Fork& operator=(Fork&&) = delete;
    void TakeFork() {
        _mutex.lock();
        _counter1.fetch_add(1);
    }

    void RemoveFork() {
        _counter2.fetch_add(1);
        _mutex.unlock();
    }
    int GetNumber() const {
        return _number;
    }
    int GetCounter1() const {
        return _counter1;
    }
    int GetCounter2() const {
        return _counter2;
    }
};

