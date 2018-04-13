/*
 * MachineConfig.hpp
 *
 *  Created on: 23 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_MACHINECONFIG_HPP_
#define EXE2_MACHINECONFIG_HPP_

#include <string>
#include <vector>
#include <iostream>
#include <regex>

/**
 * @brief struct with configuration parameters of machine
 */
struct MachineConfig
{
	int id;
	int initializationTime;
	std::vector<int> inputCapacity;
	int dryingTime;
	int productionTime;
	int MTBF;
	int repairTime;
	int STDEV;
	std::string MachineName;
	std::vector<int> parentId;
	std::vector<int> nextId;
	std::vector<int> partsNeeded;

	std::string toString();
	void fromString(std::string);
};

inline std::string MachineConfig::toString()
{
	std::ostringstream output;
	output << id << " " << initializationTime << " "
			<< dryingTime << " " << productionTime << " " << MTBF << " "
			<< repairTime << " " << STDEV << " " << MachineName << " ";
	//Convert vectors
	output << "vec ";
	std::copy(inputCapacity.begin(), inputCapacity.end(),
			std::ostream_iterator<int>(output, " "));
	output << "vec ";
	std::copy(parentId.begin(), parentId.end(),
			std::ostream_iterator<int>(output, " "));
	output << "vec ";
	std::copy(nextId.begin(), nextId.end(),
			std::ostream_iterator<int>(output, " "));
	output << "vec ";
	std::copy(partsNeeded.begin(), partsNeeded.end(),
			std::ostream_iterator<int>(output, " "));
	return output.str();
}

inline void MachineConfig::fromString(std::string input)
{
	static std::regex regex("\\d+|\\w+");
	std::regex_iterator<std::string::iterator> rit(input.begin(), input.end(),
			regex);
	std::regex_iterator<std::string::iterator> rend;
	id = std::stoi(rit->str());
	++rit;
	initializationTime = std::stoi(rit->str());
	++rit;
	dryingTime = std::stoi(rit->str());
	++rit;
	productionTime = std::stoi(rit->str());
	++rit;
	MTBF = std::stoi(rit->str());
	++rit;
	repairTime = std::stoi(rit->str());
	++rit;
	STDEV = std::stof(rit->str());
	++rit;
	MachineName = rit->str();
	++rit;
	//read out vectors
	if (rit->str() == "vec")
	{
		++rit;
		while (rit->str() != "vec")
		{
			inputCapacity.push_back(std::stoi(rit->str()));
			++rit;
		}
	}
	if (rit->str() == "vec")
	{
		++rit;
		while (rit->str() != "vec")
		{
			parentId.push_back(std::stoi(rit->str()));
			++rit;
		}
	}
	if (rit->str() == "vec")
	{
		++rit;
		while (rit->str() != "vec")
		{
			nextId.push_back(std::stoi(rit->str()));
			++rit;
		}
	}
	if (rit->str() == "vec")
	{
		++rit;
		while (rit->str() != "vec" && rit != rend)
		{
			partsNeeded.push_back(std::stoi(rit->str()));
			++rit;
		}
	}
}

#endif /* EXE1_MACHINECONFIG_HPP_ */
