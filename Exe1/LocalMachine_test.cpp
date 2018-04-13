/*
 * LocalMachine_test.cpp
 *
 *  Created on: 23 nov. 2017
 *      Author: Hendrik
 */

#include <iostream>
#include <vector>
#include <boost/test/unit_test.hpp>
#include "LocalMachine.hpp"
#include "Buffer.hpp"
#include "ProductionControl.hpp"
#define BOOST_TEST_DYN_LINK


BOOST_AUTO_TEST_SUITE( inputTest )

BOOST_AUTO_TEST_CASE( LocalTestMachineInput1 )
{
	//Making a local machine

	Buffer b1(100, 200, 1);
	Buffer b2(100, 200, 2);

	Buffer b3(199, 200, 2);


	std::map<int,Buffer> b{{2,b1},{0,b2}};

	const int machineId = 0;
	const int initTime = 0;
	/*
	 * Machine can handel 2 parts at onces
	 */

	std::vector<int> inputCapacity;
	inputCapacity.push_back(4);
	inputCapacity.push_back(2);

	const int dryingTime = 0;
	const int productionTime = 0;
	const int mtbf = 0;
	const int repairTime = 0;
	const int stdev = 0;
	const std::string machineName = "Name";
	std::vector<int> parentId;
	parentId.push_back(2);
	parentId.push_back(0);

	std::vector<int> nextId;
	nextId.push_back(1);
	nextId.push_back(2);

	std::vector<int> partsNeededVector;
	partsNeededVector.push_back(2);
	partsNeededVector.push_back(1);


	MachineConfig mc{machineId, initTime, inputCapacity, dryingTime, productionTime, mtbf, repairTime, stdev, machineName, parentId, nextId, partsNeededVector};
	LocalMachine m(mc);

	std::map<int,std::pair<int,int>> values =  m.getMachineInput(b3,b);


	const int expectedResult = 2;

	/*
	 * Input for buffer 2
	 */
	int output = values.at(2).first;

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( LocalTestMachineInput2 )
{
	//Making a local machine

	const int machineId = 0;
	const int initTime = 0;

	std::vector<int> inputCapacity;
	inputCapacity.push_back(4);
	inputCapacity.push_back(2);

	const int dryingTime = 0;
	const int productionTime = 0;
	const int mtbf = 0;
	const int repairTime = 0;
	const int stdev = 0;
	const std::string machineName = "Name";
	std::vector<int> parentId;
	parentId.push_back(2);
	parentId.push_back(5);

	std::vector<int> nextId;
	nextId.push_back(1);
	nextId.push_back(2);

	std::vector<int> partsNeededVector;
	partsNeededVector.push_back(2);
	partsNeededVector.push_back(1);


	MachineConfig mc{machineId, initTime, inputCapacity, dryingTime, productionTime, mtbf, repairTime, stdev, machineName, parentId, nextId, partsNeededVector};
	LocalMachine m(mc);

	//doing the actual test

	std::vector<int> data;

	data.push_back(5);
	data.push_back(5);
	data.push_back(5);
	data.push_back(5);
	data.push_back(5);
	data.push_back(5);




	bool output = m.ArePartsTheSame(data);
	bool expectedResult = true;

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}

BOOST_AUTO_TEST_CASE( LocalTestMachineInput3 )
{
	//Making a local machine

	const int machineId = 0;
	const int initTime = 0;

	std::vector<int> inputCapacity;
	inputCapacity.push_back(4);
	inputCapacity.push_back(2);

	const int dryingTime = 0;
	const int productionTime = 0;
	const int mtbf = 0;
	const int repairTime = 0;
	const int stdev = 0;
	const std::string machineName = "Name";
	std::vector<int> parentId;
	parentId.push_back(2);
	parentId.push_back(5);

	std::vector<int> nextId;
	nextId.push_back(1);
	nextId.push_back(2);

	std::vector<int> partsNeededVector;
	partsNeededVector.push_back(2);
	partsNeededVector.push_back(1);


	MachineConfig mc{machineId, initTime, inputCapacity, dryingTime, productionTime, mtbf, repairTime, stdev, machineName, parentId, nextId, partsNeededVector};
	LocalMachine m(mc);

	//doing the actual test

	std::vector<int> data;

	data.push_back(1);
	data.push_back(1);
	data.push_back(0);
	data.push_back(1);
	data.push_back(1);
	data.push_back(1);
	data.push_back(1);




	bool output = m.ArePartsTheSame(data);

	bool expectedResult = false;

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}


BOOST_AUTO_TEST_CASE( LocalTestMachineInput4 )
{
	//Making a local machine
	const int machineId = 0;
	const int initTime = 0;

	std::vector<int> inputCapacity;
	inputCapacity.push_back(4);
	inputCapacity.push_back(2);

	const int dryingTime = 0;
	const int productionTime = 0;
	const int mtbf = 0;
	const int repairTime = 0;
	const int stdev = 0;
	const std::string machineName = "Name";
	std::vector<int> parentId;
	parentId.push_back(2);
	parentId.push_back(5);

	std::vector<int> nextId;
	nextId.push_back(1);
	nextId.push_back(2);

	std::vector<int> partsNeededVector;
	partsNeededVector.push_back(2);
	partsNeededVector.push_back(1);


	MachineConfig mc{machineId, initTime, inputCapacity, dryingTime, productionTime, mtbf, repairTime, stdev, machineName, parentId, nextId, partsNeededVector};
	LocalMachine m(mc);

	//doing the actual test

	std::map<int, std::pair<int, int>> data;


	data[2].first = 1;
	data[2].second = 1;

	data[5].first = 4;
	data[5].second = 2;




	unsigned short output = m.getHighestInput(data);

	//Parent ID hase the higest input

	unsigned short expectedResult = 5;

	BOOST_REQUIRE_EQUAL(output,expectedResult);
}


BOOST_AUTO_TEST_SUITE_END()
