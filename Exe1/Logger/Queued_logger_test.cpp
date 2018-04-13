/*
 * Queued_logger_test.cpp
 *
 *  Created on: 5 dec. 2017
 *      Author: Kevin Taartmans
 */

#include "Queued_logger.hpp"
#include "Log_to_console.hpp"
#include "Log_to_file.hpp"

#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Queued_logger_test_module)

BOOST_AUTO_TEST_CASE(get_instance)
{
	Queued_logger& logger = Queued_logger::get_instance();
	BOOST_REQUIRE_EQUAL(logger.get_current_logger_type(), "Log_to_console");
}

BOOST_AUTO_TEST_CASE(switch_logger_type)
{
	Queued_logger& logger = Queued_logger::get_instance();
	logger.switch_logger_type(new Log_to_file("test.txt"));
	BOOST_REQUIRE_EQUAL(logger.get_current_logger_type(), "Log_to_file");
}

BOOST_AUTO_TEST_SUITE_END()
