//
// Created by Long Gong on 7/22/18.
//

#ifndef THREAD_POOL_THREAD_SAFE_QUEUE_HH
#define THREAD_POOL_THREAD_SAFE_QUEUE_HH

#include <queue>
#include <mutex>
#include <thread>


template <typename T>
class thread_safe_queue {
public:
    thread_safe_queue() = default;

    bool try_pop(T& val) {
        bool ret = false;
        _m.lock();
        if ( !_queue.empty() ) {
            val = _queue.front();
            _queue.pop();
            ret = true;
        }
        _m.unlock();
        return ret;
    }
    void push(const T& val) {
        _m.lock();
        _queue.push(val);
        _m.unlock();
    }
    void push(T&& value) {
        _m.lock();
        _queue.push(value);
        _m.unlock();
    }
protected:
    std::mutex _m{};
    std::queue<T> _queue{};
};


#endif //THREAD_POOL_THREAD_SAFE_QUEUE_HH
