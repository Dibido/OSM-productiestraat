/*
 * LocalMachine.cpp
 *
 *  Created on: 23 nov. 2017
 *      Author: Stefan
 */

#include "LocalMachine.hpp"

LocalMachine::LocalMachine(const MachineConfig& aConfig) :
		config(aConfig), state(MachineState::OFF), ready(false), active(true), currentAmountOfWork(0), stats()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
}

LocalMachine::~LocalMachine()
{

}

void LocalMachine::setConfig(const MachineConfig& aConfig)
{
	if (state == MachineState::BROKEN)
	{

		std::cout << "kapot" << std::endl;
	}
	if (state == MachineState::BUSY)
	{
		config = aConfig;
		std::cout << "busy" << std::endl;
	}
	if (state == MachineState::ON)
	{
		config = aConfig;
		std::cout << "oke" << std::endl;
	}
	if (state == MachineState::OFF)
	{
		config = aConfig;
		std::cout << "off" << std::endl;
	}
	if (state == MachineState::INIT)
	{

		config = aConfig;
		//setReady(true);

	}
//	if (state == MachineState::BROKEN)
//	{
//		setState(MachineState::ON);
//		setReady(true);
//		config = aConfig;
//	}
}

std::map<int, std::pair<int, int>> LocalMachine::getMachineInput(
		Buffer& classChildBuffer, std::map<int, Buffer> classParentBuffer)
{
	std::map<int, std::pair<int, int>> inputs;
	std::map<int, int> partsNeeded;

	for (int idx = 0; idx < classParentBuffer.size(); ++idx)
	{
		//Getting information
		int parentBuffer =classParentBuffer.find(config.parentId.at(idx))->second.getNumberOfProducts();
		int parentBufferID = classParentBuffer.find(config.parentId.at(idx))->first;
		int machineINPUT_CAPACITY = config.inputCapacity.at(idx);
		int machinePARTS_NEEDED = config.partsNeeded.at(idx);
		int childBuffer = classChildBuffer.getNumberOfProducts();
		int childMaxBuffer = classChildBuffer.getMaxBuffer();

		inputs[parentBufferID].first = 0;
		partsNeeded[parentBufferID] = machinePARTS_NEEDED;

		//Set start input
		if (parentBuffer > machineINPUT_CAPACITY)
		{
			inputs[parentBufferID].first = machineINPUT_CAPACITY;
		}
		else
		{
			inputs[parentBufferID].first = parentBuffer;
		}


		bool calulationIsRunning = true;
		while (calulationIsRunning)
		{
			if (inputs[parentBufferID].first >= machinePARTS_NEEDED)
			{
				int PartGonneBeMade = inputs[parentBufferID].first
						/ machinePARTS_NEEDED;

				inputs[parentBufferID].second = PartGonneBeMade;

				if (checkInput(machineINPUT_CAPACITY, machinePARTS_NEEDED,
						PartGonneBeMade, childMaxBuffer, childBuffer))
				{

					inputs[parentBufferID].first = PartGonneBeMade
							* machinePARTS_NEEDED;
					calulationIsRunning = false;
				}
				else
				{
					//Lower the set input input and check again if this wil work
					inputs[parentBufferID].first = (PartGonneBeMade
							* machinePARTS_NEEDED) - machinePARTS_NEEDED;


					if (inputs[parentBufferID].first <= 0)
					{
						//Thare will nog be a good result because the input value is as low as 0
						inputs[parentBufferID].second = 0;
						calulationIsRunning = false;
					}
				}
			}
			else
			{
				//Thare will not be a good result because the input value is not high enough
				inputs[parentBufferID].first = 0;
				inputs[parentBufferID].second = 0;
				calulationIsRunning = false;
			}
		}
	}

	//Checking if the parts that will be made are the same for the machine
	bool InputcalulationIsRunning = true;
	while (InputcalulationIsRunning)
	{
		std::vector<int> partsMade;
		for (auto& iter : inputs)
		{
			iter.second.second = iter.second.first / partsNeeded[iter.first];
			partsMade.push_back(iter.second.second);
		}
		if (ArePartsTheSame(partsMade))
		{
			//The parts that will be made are the same
			InputcalulationIsRunning = false;
			return inputs;
		}
		else
		{
			//Lower the highest input and try again
			inputs[getHighestInput(inputs)].first -=
					partsNeeded[getHighestInput(inputs)];
			if (inputs[getHighestInput(inputs)].second <= 0)
			{
				//There will nog be a good result because the input is set 0
				InputcalulationIsRunning = false;
			}
		}
	}
	return inputs;
}

//cppcheck-suppress functionStatic
int LocalMachine::getHighestInput(std::map<int, std::pair<int, int>> &inputs)
{
	int highest = 0;
	int highestInput;

	for (auto& iter : inputs)
	{
		if (iter.second.second > highest)
		{
			highest = iter.second.second;
			highestInput = iter.first;
		}
	}
	return highestInput;
}

//cppcheck-suppress functionStatic
bool LocalMachine::ArePartsTheSame(std::vector<int> inputs)
{
	for (int idx = 0; idx < inputs.size(); ++idx)
	{
		if (inputs.at(0) != inputs.at(idx))
		{
			return false;
		}
	}
	return true;
}

//cppcheck-suppress functionStatic
bool LocalMachine::checkInput(int machineINPUT_CAPACITY,
		int machinePARTS_NEEDED, int PartGonneBeMade, int childMaxBuffer,
		int childBuffer)
{
	return (machineINPUT_CAPACITY / machinePARTS_NEEDED >= PartGonneBeMade
			&& childMaxBuffer - childBuffer >= PartGonneBeMade);
}

void LocalMachine::printStats()
{
	std::cout << "\033[1;32mMachine " << config.id << ":\033[0m" << std::endl;
	stats.stop();
	for (auto& it : stats.timePerState)
	{
		std::cout << MachineStateToString.at(it.first) << ": " << it.second << "ms, " << it.second / 1000 / 60 /60 << "hrs" << std::endl;
	}

	unsigned long totalDayTime = IniParser::getInstance().getInt("general.NUMBER_OF_DAYS") * IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY");
	Queued_logger::get_instance().log(std::to_string(config.id)+",TimesBroken,"+ std::to_string(stats.nrOfTimesBroken));
	Queued_logger::get_instance().log(std::to_string(config.id)+",HoursWorked,"+ std::to_string(static_cast<float>(stats.timePerState.find(MachineState::BUSY)->second/60)));
	Queued_logger::get_instance().log(std::to_string(config.id)+",PercentageBroken,"+ std::to_string(static_cast<float>(stats.timePerState.find(MachineState::BROKEN)->second) / totalDayTime * 100));
	Queued_logger::get_instance().log(std::to_string(config.id)+",PercentageInitializing,"+ std::to_string(static_cast<float>(stats.timePerState.find(MachineState::INIT)->second) / totalDayTime * 100));

	std::cout << "totalDayTime: " << totalDayTime << std::endl;
	std::cout << "percentage working: " << static_cast<float>(stats.timePerState.find(MachineState::BUSY)->second / 1000 / 60 /60) / totalDayTime * 100 << "%" << std::endl;
	std::cout << "percentage broken: " << static_cast<float>(stats.timePerState.find(MachineState::BROKEN)->second / 1000 / 60 /60) / totalDayTime * 100 << "%" << std::endl;
	std::cout << "percentage initializing: " << static_cast<float>(stats.timePerState.find(MachineState::INIT)->second / 1000 / 60 /60) / totalDayTime * 100 << "%" << std::endl;

}
