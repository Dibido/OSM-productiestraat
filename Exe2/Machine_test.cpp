/*
 * Machine_test.cpp
 *
 *  Created on: 21 nov. 2017
 *      Author: Stefan
 */

#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "Machine.hpp"
#define BOOST_TEST_DYN_LINK

BOOST_AUTO_TEST_SUITE( SimulatorTest )

ProductionControl pc;
ProxyProductionControl p(&pc, nullptr);
Events events;
Clock clock;

// TODO: meerdere scenarios testen
BOOST_AUTO_TEST_CASE( TestMachineCalculateOutputParts0 )
{
	const int inputParts = 8;
	const int expectedResult = 1;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(16);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(8);

	const int id = 1;
	const int initializationTime = 10;
	const int dryingTime = 30;
	const int productionTime = 1;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateOutputParts(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( TestMachineCalculateOutputParts1 )
{
	const int inputParts = 16;
	const int expectedResult = 2;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(16);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(8);

	const int id = 1;
	const int initializationTime = 10;
	const int dryingTime = 30;
	const int productionTime = 1;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateOutputParts(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( TestMachineCalculateOutputParts2 )
{
	const int inputParts = 22;
	const int expectedResult = 22;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(40);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	const int id = 1;
	const int initializationTime = 10;
	const int dryingTime = 30;
	const int productionTime = 1;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateOutputParts(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( calculateProcessTime0 )
{
	const int inputParts = 1;
	const int productionTime = 1500;
	const int dryingTime = 0;
	const int expectedResult = 1500;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(1);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateProcessTime(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( calculateProcessTime1 )
{
	const int inputParts = 8;
	const int productionTime = 60000;
	const int dryingTime = 30;
	const int expectedResult = 1860000;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(40);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateProcessTime(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( startWork0 )
{
	const int inputParts = 8;
	const int productionTime = 1;
	const int dryingTime = 30;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(7);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	BOOST_CHECK_THROW(m.startWork(inputParts), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( startWork1 )
{
	const int inputParts = 8;
	const int productionTime = 1;
	const int dryingTime = 30;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(8);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	BOOST_REQUIRE_NO_THROW(m.startWork(inputParts));
}

BOOST_AUTO_TEST_CASE( startWork2 )
{
	const int inputParts = 3;
	const int productionTime = 1;
	const int dryingTime = 30;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(8);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(2);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	BOOST_CHECK_THROW(m.startWork(inputParts), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( startWork3 )
{
	const int inputParts = 17;
	const int productionTime = 1;
	const int dryingTime = 30;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(40);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(8);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	BOOST_CHECK_THROW(m.startWork(inputParts), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE( startWork4 )
{
	const int inputParts = 16;
	const int productionTime = 1;
	const int dryingTime = 30;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(40);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(8);

	const int id = 1;
	const int initializationTime = 10;
	const int MTBF = 2000;
	const int repairTime = 8;
	const float STDEV = 0.5;
	const std::string MachineName = "ZAGEN";
	std::vector<int> parentId;
	parentId.push_back(1);
	std::vector<int> nextId;
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};

	Machine m(&p, mc, &events, &clock);

	BOOST_REQUIRE_NO_THROW(m.startWork(inputParts));
}

const int id = 1;
const int initializationTime = 10;
const int MTBF = 2000;
const int repairTime = 8;
const float STDEV = 0.5;
const std::string MachineName = "ZAGEN";
std::vector<int> parentId;
std::vector<int> nextId;

BOOST_AUTO_TEST_CASE( calculateProcessTime2 )
{
	const int inputParts = 1;
	const int productionTime = 60000;
	const int dryingTime = 20;
	const int expectedResult = 1260000;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(3);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	parentId.push_back(1);
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};
	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateProcessTime(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}
BOOST_AUTO_TEST_CASE( calculateProcessTime3 )
{
	const int inputParts = 3;
	const int productionTime = 60000;
	const int dryingTime = 20;
	const int expectedResult = 1260000;
	std::vector<int> inputCapacity;
	inputCapacity.push_back(3);
	std::vector<int> partsNeeded;
	partsNeeded.push_back(1);

	parentId.push_back(1);
	nextId.push_back(2);
	MachineConfig mc{ id, initializationTime, inputCapacity, dryingTime, productionTime, MTBF, repairTime, STDEV, MachineName, parentId, nextId, partsNeeded};
	Machine m(&p, mc, &events, &clock);

	m.startWork(inputParts);
	int output = m.calculateProcessTime(inputParts, m.getConfig());

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_SUITE_END()
