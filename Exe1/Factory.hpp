/*
 * Factory.hpp
 *
 *  Created on: Dec 19, 2017
 *      Author: Kevin Taartmans
 */

#ifndef EXE1_FACTORY_HPP_
#define EXE1_FACTORY_HPP_

#include <string>
#include <map>
#include <iostream>

#include "ConfigStructs.hpp"
#include "IniParser/IniParser.hpp"
#include "../Exe2/MachineConfig.hpp"
#include "ProductionScheduling.hpp"

/**
 * @brief This class represents the factory. Within this class the simulation can be started with startSimulation()
 */
class Factory
{
public:
	Factory();
	virtual ~Factory();
	/**
	 * @brief Call this function to start the simulation
	 */
	void startSimulation(const std::string& pathToIni);
private:
	void getPathsFromMaster(const std::string& pathToIni);
	void getDataFromMaster(const std::string& pathToIni);
	MachineConfig LoadMachineConfiguration(int machineNumber, const std::string& pathToIni);
	BufferConfig LoadBufferConfiguration(int bufferNumber, const std::string& pathToIni);

	std::vector<std::string>pathVector;
	GlobalConfig gc;
	std::vector<ProductionLineConfig>ProductionLineConfigVector;
};

#endif /* EXE1_FACTORY_HPP_ */
