/*
 * Queue.cpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#include "Queue.hpp"

void Queue::enqueue(const std::string& log_data)
{
	std::unique_lock<std::mutex> lock(queue_busy);
	queue.push(log_data);
	queue_not_empty.notify_one();
}

std::string Queue::dequeue()
{
	std::unique_lock<std::mutex> lock(queue_busy);
	while (queue.size()==0) queue_not_empty.wait(lock);

	std::string front = queue.front();
	queue.pop();
	return front;
}
