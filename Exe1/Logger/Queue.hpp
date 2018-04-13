/*
 * Queue.hpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include <queue>
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>

class Queue
{
	public:
		/**
		 * @brief puts a string in the queue. locks mutex when it does
		 * @author Bram Knippenberg
		 * @param log_data
		 */
		void enqueue(const std::string& log_data);
		/**
		 * @brief retrieves a string in the queue, locks mutex when it does.
		 * @author Bram Knippenberg
		 * @return the first string in the queue
		 */
		std::string dequeue();

		/**
		 * @brief returns the size of the queue (surprise surprise)
		 */
		size_t size() const
		{
			return queue.size();
		}

	private:
		std::queue<std::string> queue;
		std::mutex queue_busy;
		std::condition_variable queue_not_empty;
};

#endif /* QUEUE_HPP_ */
