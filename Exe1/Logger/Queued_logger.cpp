/*
 * Queued_logger.cpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#include "Queued_logger.hpp"
#include "Log_to_console.hpp"


/*static*/ Queued_logger& Queued_logger::get_instance()
{
	static Queued_logger the_logger(new Log_to_console());
	return the_logger;
}

Queued_logger::Queued_logger(Logger_instance* logger_instance)
: my_logger(logger_instance)
{
	my_logger->connect();
	t = std::thread(&Queued_logger::write_to_log_output, this);
	t.detach();
}


void Queued_logger::switch_logger_type(Logger_instance* logger_instance)
{
	is_stopped = true; // stops threads that are currently consuming the queue
	Logger_instance* old = my_logger;

	logger_instance->connect();
	my_logger = logger_instance;	//new logger should be connected before this assignment or threading error will occur

	old->disconnect();
	delete old;
	is_stopped = false; // flips the boolean back so new threads can be started
	t = std::thread(&Queued_logger::write_to_log_output, this);
	t.detach();
}


Queued_logger::~Queued_logger()
{
	is_stopped = true;
	my_logger->disconnect();
	delete my_logger;
}

void Queued_logger::log(const std::string& log_data)
{
	queue.enqueue(log_data);
}

void Queued_logger::write_to_log_output()
{
	while (!is_stopped)
	{
		my_logger->log(queue.dequeue());
		stop_condition.notify_one();
	}
}

void Queued_logger::stop()
{
	std::unique_lock<std::mutex> lock(stop_mutex);
	stop_condition.wait(lock, [&]{ return queue.size() == 0; });
}

