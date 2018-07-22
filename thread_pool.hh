//
// Created by Long Gong on 7/22/18.
//

#ifndef THREAD_POOL_THREAD_POOL_HH
#define THREAD_POOL_THREAD_POOL_HH

#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include <queue>
#include <future>
#include "thread_safe_queue.hh"

/**
 *
 * Copy from "C++ Concurrency in Action"
 */
class JoinThreads {
protected:
    std::vector<std::thread> &_threads;
public:
    explicit JoinThreads(std::vector<std::thread> &threads) :
            _threads(threads) {}

    ~JoinThreads() {
        for (auto &th: _threads) {
            if (th.joinable()) th.join();
        }
    }
};

/**
 *
 * Copy from "C++ Concurrency in Action"
 */
class ThreadPool {
protected:
    std::atomic_bool _done;
    thread_safe_queue<std::function<void()> > _work_queue;
    std::vector<std::thread> _threads;
    JoinThreads _joiner;

    void worker_thread() {
        while ( !_done ) {
            std::function<void()> task;
            if ( _work_queue.try_pop(task) ) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

public:
    explicit ThreadPool(size_t thread_num = 0):
            _done(false), _joiner(_threads){
        size_t thread_count = thread_num;
        if ( thread_count == 0 )
            thread_count = std::thread::hardware_concurrency();

        for ( size_t i = 0;i < thread_count; ++ i )
            _threads.emplace_back(&ThreadPool::worker_thread, this);

    }
    ~ThreadPool(){
        _done = true;
    }
    template <typename FunctionType>
    void submit(FunctionType f) {
        _work_queue.push(std::function<void()>(f));
    }
};


#endif //THREAD_POOL_THREAD_POOL_HH
