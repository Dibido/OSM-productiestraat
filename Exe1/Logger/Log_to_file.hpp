/*
 * Log_to_file.hpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#ifndef LOG_TO_FILE_HPP_
#define LOG_TO_FILE_HPP_

#include <string>
#include <fstream>
#include <mutex>
#include <iostream>

#include "Logger_instance.hpp"

class Log_to_file : public Logger_instance
{
public:
	/**
	 * @brief initialises the output filename
	 * @author Bram Knippenberg
	 * @param output_file
	 */
	//cppcheck-suppress noExplicitConstructor
	explicit Log_to_file(const std::string& output_file);

	virtual ~Log_to_file();

	/**
	 * @brief connects the output with the file.
	 * @author Bram Knippenberg
	 */
	/*virtual*/ void connect();

	/**
	 * @brief In this function you write to the file
	 * @author Bram Knippenberg
	 * @param log_data, the string thats written to output
	 */
	/*virtual*/ void log(const std::string& log_data);

	/**
	 * @brief Closes the file where we wrote too earlier
	 * @author Bram Knippenberg
	 */
	/*virtual*/ void disconnect();

	/**
	 * @brief function for getting current logger name. FOR TESTING PURPOSES ONLY
	 * @author Kevin Taartmans
	 * @return name of current logger
	 */
	/*virtual*/ std::string get_current_logger_type() {return name;};

	std::string my_output_file_file_name;
	std::ofstream my_output_file;
private:
	std::string name = "Log_to_file";
	std::mutex file_lock;
};

#endif /* LOG_TO_FILE_HPP_ */
