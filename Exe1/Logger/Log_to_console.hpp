/*
 * Log_to_console.hpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#ifndef LOG_TO_CONSOLE_HPP_
#define LOG_TO_CONSOLE_HPP_

#include <string.h>
#include <iostream>
#include <thread>

#include "Logger_instance.hpp"

class Log_to_console : public Logger_instance
{
public:
	Log_to_console();
	virtual ~Log_to_console();

	/**
	 * @brief This is an empty function. Cout doesn't need to connect.
	 * @author Bram Knippenberg
	 */
	/*virtual*/ void connect();

	/**
	 * @brief In this function you write to the console
	 * @author Bram Knippenberg
	 * @param log_data, the string thats written to output
	 */
	/*virtual*/ void log(const std::string& log_data);

	/**
	 * @brief This is an empty function. Cout doesn't need to disconnect.
	 * @author Bram Knippenberg
	 */
	/*virtual*/ void disconnect();

	/**
	 * @brief function for getting current logger name. FOR TESTING PURPOSES ONLY
	 * @author Kevin Taartmans
	 * @return name of current logger
	 */
	/*virtual*/ std::string get_current_logger_type() {return name;};
private:
	std::string name = "Log_to_console";
};

#endif /* LOG_TO_CONSOLE_HPP_ */
