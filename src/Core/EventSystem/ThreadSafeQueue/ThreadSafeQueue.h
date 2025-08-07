#pragma once

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cv;

public:
    void push(const T& item)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(item);
        }
        m_cv.notify_one();
    }

    T waitAndPop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [&]{ return !m_queue.empty(); });
        T item = m_queue.front();
        m_queue.pop();

        return item;
    }

    bool tryPop(T& item)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        if (m_queue.empty()) return false;

        item = m_queue.front();
        m_queue.pop;

        return true;
    }
};