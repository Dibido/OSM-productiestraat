/*
 * ConfigStructs.hpp
 *
 *  Created on: Dec 21, 2017
 *      Author: ktaar
 */

#ifndef EXE1_CONFIGSTRUCTS_HPP_
#define EXE1_CONFIGSTRUCTS_HPP_

#include <map>
#include <string>
#include "../Exe2/MachineConfig.hpp"

struct GlobalConfig
{
	int seed;
	std::string localIp;
	int localPort;
	std::string productionControlIp;
	int productionControlPort;
	std::string pathForLog;
	int numberOfDays;
	int numberOfHoursPerDay;
	int morningStartTime;
};

struct BufferConfig
{
	int numberOfProducts;
	int maxBuffer;
	int id;
};

struct ProductionLineConfig
{
	int totalAmountToProduce;
	int batchSize;
	int number_of_machines;
	int number_of_buffers;
	std::map<int, MachineConfig> mcm;
	std::map<int, BufferConfig> bcm;
};

#endif /* EXE1_CONFIGSTRUCTS_HPP_ */
