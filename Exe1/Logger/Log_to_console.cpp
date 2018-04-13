/*
 * Log_to_console.cpp
 *
 * Created on: 13 okt. 2016
 *   Author: Bram Knippenberg
 * Edited on: 15 nov. 2017
 *   Editor: Kevin Taartmans
 */

#include "Log_to_console.hpp"



Log_to_console::Log_to_console()
{
}

Log_to_console::~Log_to_console()
{
}

void Log_to_console::connect()
{
}

void Log_to_console::log(const std::string& log_data)
{
	std::cout << log_data << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(500)); //in order to show consumer delay
}

void Log_to_console::disconnect()
{
}
