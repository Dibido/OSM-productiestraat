/*
 * LocalMachine_test.cpp
 *
 *  Created on: 23 nov. 2017
 *      Author: Hendrik
 */

#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "ProductionControl.hpp"
#include "LoadConfiguration.hpp"

#include "Buffer.hpp"
#define BOOST_TEST_DYN_LINK


BOOST_AUTO_TEST_SUITE( ProductionControlCheck )

BOOST_AUTO_TEST_CASE( ProductionControlCheck1 )
{
	IniParser::getInstance().setFile("../../Exe1/configDureMachineDureTafel_testing.ini");
	MachineNetworkHandlerPtr mnhPtr = std::make_shared<machineNetworkHandler>(nullptr);

	ProductionControl p(mnhPtr);
	p.init("../../Exe1/configForUnitTest.ini");

	std::map<unsigned long, unsigned long> b = p.getFirstBuffers();

	unsigned long expectedResult = 3;

	BOOST_REQUIRE_EQUAL(b.size(),expectedResult);

}

BOOST_AUTO_TEST_CASE( ProductionControlCheck2 )
{
	IniParser::getInstance().setFile("../../Exe1/configDureMachineDureTafel_testing.ini");
	MachineNetworkHandlerPtr mnhPtr = std::make_shared<machineNetworkHandler>(nullptr);

	ProductionControl p(mnhPtr);
	p.init("../../Exe1/configForUnitTest.ini");

	std::map<unsigned long, unsigned long> b = p.calculateFirstBufferSize();

	unsigned long expectedResult = 648;
	unsigned long expectedResult2 = 1152;
	unsigned long expectedResult3 = 720;

	unsigned long output = b.find(7)->second;
	unsigned long output2 = b.find(5)->second;
	unsigned long output3 = b.find(0)->second;

	BOOST_REQUIRE_EQUAL(output,expectedResult);
	BOOST_REQUIRE_EQUAL(output2,expectedResult2);
	BOOST_REQUIRE_EQUAL(output3,expectedResult3);

}

BOOST_AUTO_TEST_SUITE_END()
