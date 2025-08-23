//#pragma once
//
//#include <mutex>
//#include <queue>
//#include <condition_variable>
//
//template <typename T>
//class ThreadSafeQueue
//{
//    std::queue<T> m_queue;
//    //std::mutex m_mutex;
//    //std::condition_variable m_cv;
//
//public:
//    void push(T&& item)
//    {
//        //{
//            //std::lock_guard<std::mutex> lock(m_mutex);
//            m_queue.push(std::move(item));
//        //}
//        //m_cv.notify_one();
//    }
//
//    T waitAndPop()
//    {
//        //std::unique_lock<std::mutex> lock(m_mutex);
//        //m_cv.wait(lock, [&]{ return !m_queue.empty(); });
//        T item = std::move(m_queue.front());
//        m_queue.pop();
//
//        return item;
//    }
//
//    bool tryPop(T& item)
//    {
//        //std::lock_guard<std::mutex> lock(m_mutex);
//
//        if (m_queue.empty()) return false;
//
//        item = std::move(m_queue.front());
//        m_queue.pop();
//
//        return true;
//    }
//
//    bool hasEvent()
//    {
//        return !m_queue.empty();
//    }
//};

#pragma once 
#include <vector>
#include <atomic>
#include <optional>
#include <thread>
#include <cassert>

template<typename T, size_t Capacity>
class ThreadSafeQueue
{
	static_assert((Capacity& (Capacity - 1)) == 0,
		"Capacity must be power of 2 for mask optimization");
	std::vector<T> m_buffer;
	std::atomic<size_t> m_head{ 0 };
	std::atomic<size_t> m_tail{ 0 };

	public:
		ThreadSafeQueue() : m_buffer(Capacity) {}

	// Producer: Push an event
	bool push(T&& item)
	{
		size_t head = m_head.load(std::memory_order_relaxed);
		size_t next = (head + 1) & (Capacity - 1);

		if (next == m_tail.load(std::memory_order_acquire))
		{
			// Buffer full
			return false;
		}

		m_buffer[head] = std::move(item);
		m_head.store(next, std::memory_order_release);
		return true;
	}

	// Consumer: Pop event
	std::optional<T> pop()
	{
		size_t tail = m_tail.load(std::memory_order_relaxed);

		if (tail == m_head.load(std::memory_order_acquire))
		{
			// Buffer empty
			return std::nullopt;
		}

		T item = std::move(m_buffer[tail]);
		m_tail.store((tail + 1) & (Capacity - 1), std::memory_order_release);
		return item;
	}

	bool empty() const
	{
		return m_head.load(std::memory_order_acquire) == m_tail.load(std::memory_order_acquire);
	}
};