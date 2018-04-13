/*
 * Factory.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: Kevin Taartmans
 */

#include "Factory.hpp"

Factory::Factory()
:gc(GlobalConfig {})
{
	// TODO Alle ini files aanpassen op nieuw formaat
}

Factory::~Factory()
{
	// TODO Auto-generated destructor stub
}

//cppcheck-suppress functionStatic
void Factory::startSimulation(const std::string& pathToIni)
{
	IniParser::getInstance().setFile(pathToIni);
	getPathsFromMaster(pathToIni);
	getDataFromMaster(pathToIni);

	std::map<int, MachineConfig> mcm;
	std::map<int, BufferConfig> bcm;

	for (int i = 0; i < pathVector.size(); ++i)
	{
		IniParser::getInstance().setFile(pathVector.at(i));
		int totalAmount = IniParser::getInstance().getInt("general.TOTAL_AMOUNT_TO_PRODUCE");
		int batchSize = IniParser::getInstance().getInt("general.BATCH_SIZE");
		int numberOfMachines = IniParser::getInstance().getInt("general.NUMBER_OF_MACHINES");
		int numberOfBuffers = IniParser::getInstance().getInt("general.NUMBER_OF_BUFFERS");

		for (int j = 0; j < numberOfMachines; ++j)
		{
			MachineConfig mc = LoadMachineConfiguration(j, pathVector.at(i));
			mcm.insert(std::make_pair(mc.id, mc));
		}
		for (int j = 0; j < numberOfBuffers; ++j)
		{
			BufferConfig bc = LoadBufferConfiguration(j, pathVector.at(i));
			bcm.insert(std::make_pair(bc.id, bc));
		}
		DEBUG_MSG("mcm.size: " << mcm.size());
		DEBUG_MSG("bcm.size: " << bcm.size());
		ProductionLineConfigVector.push_back(
			ProductionLineConfig
			{
				totalAmount,
				batchSize,
				numberOfMachines,
				numberOfBuffers,
				mcm,
				bcm
			}
		);
		mcm.clear();
		bcm.clear();
	}
	IniParser::getInstance().setFile("../../Exe1/master.ini");
	FactoryClock::getInstance()->setRunning(true);
	#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
	#define PBWIDTH 60
	std::thread([this]()
	{
		for(;FactoryClock::getInstance()->isRunning();)
		{
			double percentage = (double)((FactoryClock::getInstance()->getSimulationTime().total_seconds() / 60 / 60 / 24) / (double)gc.numberOfDays);
			int val = (int) (percentage * 100);
			int lpad = (int) (percentage * PBWIDTH);
			int rpad = PBWIDTH - lpad;
			printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
			fflush (stdout);
			std::this_thread::sleep_for (std::chrono::milliseconds(100));
		}
	}).detach();

	ProductionScheduling scheduling;
	while(((FactoryClock::getInstance()->getSimulationTime().total_seconds()/60)/60) < gc.numberOfDays * 24)
	{

		scheduling.processOrder(ProductionLineConfigVector);
	}

//  uncomment this to verify output
	for(auto plcv : ProductionLineConfigVector)
	{
		DEBUG_MSG("[PLCV] BATCH SIZE: " << plcv.batchSize);
		for(auto mmap : plcv.mcm)
		{
			DEBUG_MSG("[MAP | FIRST] MACHINE ID: " << mmap.first);
			DEBUG_MSG("[MAP | SECOND] MACHINE NAME: " << mmap.second.MachineName);
		}
	}
}

void Factory::getPathsFromMaster(const std::string& pathToIni)
{
	IniParser::getInstance().setFile(pathToIni);
	std::stringstream pathsStringStream(IniParser::getInstance().getString("paths.PATHS"));
	std::string pathVectorData;
	while (pathsStringStream >> pathVectorData)
	{
		pathVector.push_back(pathVectorData);
	}
}

void Factory::getDataFromMaster(const std::string& pathToIni)
{
	IniParser::getInstance().setFile(pathToIni);
	gc.seed = IniParser::getInstance().getInt("general.SEED");
	gc.localIp = IniParser::getInstance().getString("general.LOCAL_IP");
	gc.localPort = IniParser::getInstance().getInt("general.LOCAL_PORT");
	gc.productionControlIp = IniParser::getInstance().getString("general.PRODUCTION_CONTROL_IP");
	gc.productionControlPort = IniParser::getInstance().getInt("general.PRODUCTION_CONTROL_PORT");
	gc.pathForLog = IniParser::getInstance().getString("general.PATH_FOR_LOG");
	gc.numberOfDays = IniParser::getInstance().getInt("general.NUMBER_OF_DAYS");
	gc.numberOfHoursPerDay = IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY");
	gc.morningStartTime = IniParser::getInstance().getInt("general.MORNING_START_TIME");
}

MachineConfig Factory::LoadMachineConfiguration(int machineNumber, const std::string& pathToIni)
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
	{
		machineId,
		initTime,
		inputCapVector,
		dryingTime,
		productionTime,
		mtbf,
		repairTime,
		stdev,
		machineName,
		parentIdVector,
		childIdVector,
		partsNeededVector,
	};
	return machine;
}

BufferConfig Factory::LoadBufferConfiguration(int bufferNumber, const std::string& pathToIni)
{
	BufferConfig newBufferConfig;
	newBufferConfig.id = IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".ID"),
	newBufferConfig.maxBuffer = IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".MAX_SIZE"),
	newBufferConfig.numberOfProducts = IniParser::getInstance().getInt("buffer"+std::to_string(bufferNumber)+".PRODUCTS");
	return newBufferConfig;
}
