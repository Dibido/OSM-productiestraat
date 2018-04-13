/*
 * Queued_logger.hpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#ifndef QUEUED_LOGGER_HPP_
#define QUEUED_LOGGER_HPP_

#include <string>
#include <thread>
#include <iostream>
#include <mutex>
#include <condition_variable>

#include "Logger_instance.hpp"
#include "Queue.hpp"

/**
 * This logger is based on a Singleton design pattern and Producer Consumer design pattern
 * The loggers output can be changed from logging to console to logging to a file.
 */
class Queued_logger
{
public:
	/**
	 * @brief returns the instance of the logger. Default action is to log to console
	 * @author Bram Knippenberg
	 * @return logger instance
	 */
	static Queued_logger& get_instance();

	/**
	 * @brief changes what type of logger is used. function will stop logger threads,
	 * 		disconnect the previous logger and then connects the new logger. Old logger will be deleted after.
	 * @author Bram Knippenberg, edited by Kevin Taartmans
	 * @param logger_instance, the type of preferred logger.
	 */
	void switch_logger_type(Logger_instance* logger_instance);

	/**
	 * @brief sends messages to the queue.
	 * @author Bram Knippenberg
	 * @param log_data, string format
	 */
	void log(const std::string& log_data);

	virtual ~Queued_logger();

	/**
	 * @brief function for getting current logger name. FOR TESTING PURPOSES ONLY
	 * @author Kevin Taartmans
	 * @return name of current logger
	 */
	std::string get_current_logger_type()
	{
		return my_logger->get_current_logger_type();
	};

	/**
	 * @brief get queue size
	 * @author Kevin Taartmans
	 * @return int size
	 */
	const int get_queue_size() const
	{
		return queue.size();
	};

	void stop();


private:
	bool is_stopped = false;
	std::thread t;
	std::condition_variable stop_condition;
	std::mutex stop_mutex;
	//cppcheck-suppress noExplicitConstructor
	explicit Queued_logger(Logger_instance* logger_instance);
	Queue queue;
	Logger_instance* my_logger;

	/**
	 * @brief Starts the consumer classes
	 * @author Bram Knippenberg
	 */
	void write_to_log_output();
};

#endif /* QUEUED_LOGGER_HPP_ */
