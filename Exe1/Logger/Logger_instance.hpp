/*
 * Logger_instance.hpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#ifndef LOGGER_INSTANCE_HPP_
#define LOGGER_INSTANCE_HPP_

#include <string>

class Logger_instance {
public:
	virtual ~Logger_instance(){}

	/**
	 * @brief pure virtual method.
	 * In this function you connect with the output file if necessary.
	 * @author Bram Knippenberg
	 */
	virtual void connect()=0;

	/**
	 * @brief pure virtual method.
	 * In this function you write to the output file/console
	 * @author Bram Knippenberg
	 * @param log_data, the string thats written to output
	 */
	virtual void log(const std::string& log_data)=0;

	/**
	 * @brief pure virtual method.
	 * In this function you disconnect with the output file if necessary.
	 * @author Bram Knippenberg
	 */
	virtual void disconnect()=0;

	/**
	 * @brief pure virtual method.
	 * @author Kevin Taartmans
	 * @return this function returns the name of output type
	 */
	virtual std::string get_current_logger_type()=0;
};

#endif /* LOGGER_INSTANCE_HPP_ */
