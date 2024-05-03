//
// Created by Administrator on 2024/5/1.
//

#ifndef P20_CODE_SAFEQUEUE_H
#define P20_CODE_SAFEQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <QByteArray>

template <typename T>
class SafeQueue {
private:
    std::queue<T> queue;
    std::mutex mutex;
    std::condition_variable condvar;

public:
    void push(T value){
        std::lock_guard<std::mutex> lock(mutex);
        queue.push(std::move(value));
        condvar.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(mutex);
        while(queue.empty()) {
            condvar.wait(lock);
        }
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    bool empty() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.empty();
    }

    T front() {
        std::lock_guard<std::mutex> lock(mutex);
        return queue.front();
    }
};
#endif //P20_CODE_SAFEQUEUE_H
