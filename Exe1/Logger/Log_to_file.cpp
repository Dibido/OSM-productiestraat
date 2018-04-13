/*
 * Log_to_file.cpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#include "Log_to_file.hpp"

Log_to_file::Log_to_file(const std::string& output_file)
: my_output_file_file_name(output_file)
{
}

Log_to_file::~Log_to_file()
{
}

void Log_to_file::connect()
{
	if(std::ifstream(my_output_file_file_name))
	{
		if(remove(my_output_file_file_name.c_str()) != 0 )
		{
			throw std::runtime_error("Error deleting previous log file");
		}
	}
	my_output_file.open(my_output_file_file_name, std::ios::out | std::ios::app);
}

void Log_to_file::log(const std::string& log_data)
{
	std::unique_lock<std::mutex> lock(file_lock);
	my_output_file << log_data << std::endl;
}

void Log_to_file::disconnect()
{
	my_output_file.close();
}
