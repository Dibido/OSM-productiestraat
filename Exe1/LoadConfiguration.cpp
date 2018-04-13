/*
 * LoadConfiguration.cpp
 *
 *  Created on: 21 nov. 2017
 *      Author: jacol
 */

#include "LoadConfiguration.hpp"

LoadConfiguration::LoadConfiguration()
{
}

LoadConfiguration::~LoadConfiguration()
{
}

Buffer LoadConfiguration::LoadBufferConfiguration(int bufferNumber)
{
	Buffer newBuffer(
			IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".PRODUCTS"),
			IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".MAX_SIZE"),
			IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".ID"));

	return newBuffer;
}

/*static*/MachineConfig LoadConfiguration::LoadMachineConfiguration(
		int machineNumber)
{
	int machineId = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".ID");
	int initTime = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".INITIALIZATIONTIME");
	std::string inputCap = IniParser::getInstance().getString(
			"machine" + std::to_string(machineNumber) + ".INPUT_CAPACITY");
	int dryingTime = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".DRYINGTIME");
	int productionTime = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".PRODUCTIONTIME");
	int mtbf = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".MTBF");
	int repairTime = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".REPAIR_TIME");
	int stdev = IniParser::getInstance().getInt(
			"machine" + std::to_string(machineNumber) + ".STDEV");
	std::string machineName = IniParser::getInstance().getString(
			"machine" + std::to_string(machineNumber) + ".MACHINE_NAME");
	std::string parentId = IniParser::getInstance().getString(
			"machine" + std::to_string(machineNumber) + ".PARENT_ID");
	std::string childId = IniParser::getInstance().getString(
			"machine" + std::to_string(machineNumber) + ".CHILD_ID");
	std::string partsNeeded = IniParser::getInstance().getString(
			"machine" + std::to_string(machineNumber) + ".PARTS_NEEDED");

	std::stringstream inputCapStringStream(inputCap);
	std::stringstream parentIdStringStream(parentId);
	std::stringstream childIdStringStream(childId);
	std::stringstream partsNeededStringStream(partsNeeded);

	std::vector<int> inputCapVector;
	std::vector<int> parentIdVector;
	std::vector<int> childIdVector;
	std::vector<int> partsNeededVector;

	int inputCapData;
	int parentIdData;
	int childIdData;
	int partsNeededData;
	while (inputCapStringStream >> inputCapData)
	{
		inputCapVector.push_back(inputCapData);
	}
	while (parentIdStringStream >> parentIdData)
	{
		parentIdVector.push_back(parentIdData);
	}
	while (childIdStringStream >> childIdData)
	{
		childIdVector.push_back(childIdData);
	}
	while (partsNeededStringStream >> partsNeededData)
	{
		partsNeededVector.push_back(partsNeededData);
	}

	MachineConfig machine
	{ machineId, initTime, inputCapVector, dryingTime,
			productionTime, mtbf, repairTime, stdev, machineName,
			parentIdVector, childIdVector, partsNeededVector };
	return machine;
}

void LoadConfiguration::makeMachines(ProductionControl* pc,  MachineNetworkHandlerPtr mnhPtr, std::string configFile,
		std::map<int, ProxyMachine>& aMachine,
		std::map<int, LocalMachine>& aLocalMachine,
		std::map<int, Buffer>& aBuffers, ProxyProductionControl* ppc)
{
	IniParser::getInstance().setFile(configFile);
	int NUMBER_OF_MACHINES = IniParser::getInstance().getInt(
			"general.NUMBER_OF_MACHINES");
	int NUMBER_OF_BUFFERS = IniParser::getInstance().getInt(
			"general.NUMBER_OF_BUFFERS");
	for (size_t i = 0; i < NUMBER_OF_BUFFERS; ++i)
	{
		Buffer buffer = LoadBufferConfiguration(i);
		aBuffers.insert(std::pair<unsigned long, Buffer>(buffer.getId(), buffer));
	}

	for (size_t i = 0; i < NUMBER_OF_MACHINES; ++i)
	{
		MachineConfig machine = LoadMachineConfiguration(i);

		aLocalMachine.insert(std::pair<int, LocalMachine>(machine.id, (LocalMachine(machine))));
		aMachine.insert(std::pair<int, ProxyMachine>(machine.id, ProxyMachine(machine, mnhPtr, ppc)));
	}
}
