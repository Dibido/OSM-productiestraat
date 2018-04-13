/*
 * LoadConfiguration.hpp
 *
 *  Created on: 21 nov. 2017
 *      Author: jacol
 */

#ifndef LoadCONFIGURATION_HPP_
#define LoadCONFIGURATION_HPP_

#include <map>
#include <string>

#include "IniParser/IniParser.hpp"

#include "ProductionControl.hpp"
#include "../Exe2/ProxyProductionControl.hpp"
#include "ProxyMachine.hpp"
#include "Buffer.hpp"
#include "LocalMachine.hpp"
#include "Network/machineNetworkHandler.hpp"

class ProxyMachine;
class ProductionControl;
class ProxyProductionControl;

/**
 * @brief class to load configuration using IniParser, create machines, buffers and machineConfigs.
 */
class LoadConfiguration
{
public:
	/**
	 * @brief Constructor
	 */
	LoadConfiguration();
	virtual ~LoadConfiguration();

	/**
	 * @brief Loads the configuration values from a file, creates a buffer object and returns it
	 * @param i Buffer number in the configuration file
	 * @return Buffer
	 */
	static Buffer LoadBufferConfiguration(int bufferNumber);

	/**
	 * @brief Loads the configuration values from a file, parses strings (with multiple integer values) to a vector, and returns it
	 * @param j Machine number in the configuration file
	 * @return MachineConfig
	 */
	static MachineConfig LoadMachineConfiguration(int machineNumber);

	/**
	 * @brief Fills the buffer list, machineconfig list, machine list
	 * @param configFile
	 * @param aMachine
	 * @param aMachineConfig
	 * @param aBuffers
	 * @param pc
	 */
	void makeMachines(ProductionControl* pc, MachineNetworkHandlerPtr mnhPtr, std::string configFile, std::map<int,ProxyMachine>& aMachine, std::map<int,LocalMachine>& aLocalMachine, std::map<int,Buffer>& aBuffers, ProxyProductionControl* ppc);

};

#endif /* LoadCONFIGURATION_HPP_ */
