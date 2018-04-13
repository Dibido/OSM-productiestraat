/*
 * LocalMachine.hpp
 *
 *  Created on: 23 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE1_LOCALMACHINE_HPP_
#define EXE1_LOCALMACHINE_HPP_
#include <map>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Logger/Queued_logger.hpp"
#include "Logger/Log_to_file.hpp"

#include "../Exe2/MachineCalculations.hpp"
#include "../Exe2/MachineConfig.hpp"
#include "../Exe2/MachineState.hpp"
#include "FactoryClock.hpp"
#include "Buffer.hpp"
#include "IniParser/IniParser.hpp"

/**
 * @brief struct that saves the some statistics of a machine
 */
struct MachineStatistics
{
	std::map<MachineState, unsigned long long> timePerState;
	unsigned long long nrOfTimesBroken;

	MachineState state;
	boost::posix_time::time_duration inStateSince;
	/**
	 * @brief constructor
	 */
	MachineStatistics()
	: timePerState(), nrOfTimesBroken(0), state(MachineState::OFF), inStateSince(0,0,0)
	{
	};
	/**
	 * @brief sets the state of the statisics and updates the timePerState
	 * @param state state that the machine goes to
	 */
	void setState(MachineState state)
	{
		if (state == MachineState::BROKEN)
		{
			++nrOfTimesBroken;
		}
		if (timePerState.count(this->state) > 0)
		{
			timePerState.find(this->state)->second += (FactoryClock::getInstance()->getSimulationTime().total_milliseconds() - inStateSince.total_milliseconds());
		}
		else
		{
			timePerState.emplace(std::make_pair(this->state, (FactoryClock::getInstance()->getSimulationTime().total_milliseconds() - inStateSince.total_milliseconds())));
		}
		this->state = state;
		inStateSince = FactoryClock::getInstance()->getSimulationTime();
	}
	/**
	 * @brief function updates the timePerState at the end of simulation, should be called before printing statistics
	 */
	void stop()
	{
		timePerState.find(this->state)->second += (FactoryClock::getInstance()->getSimulationTime().total_milliseconds() - inStateSince.total_milliseconds());
		this->state = MachineState::OFF;
	}
};

/**
 * @brief local machine class which stores configurations struct and has local calculate funcions
 */
class LocalMachine : public MachineCalculations
{
public:

	/**
	 * @brief constructor
	 * @param aConfig configuration
	 */
	explicit LocalMachine(const MachineConfig& aConfig);

	/**
	 * @brief destructor
	 */
	virtual ~LocalMachine();
	/**
	 * @brief set the configuration of the system
	 * @pre -
	 * @post configuration of machine is set
	 * @param
	 */
	void setConfig(const MachineConfig& aConfig);

	const MachineConfig& getConfig() const
	{
		return config;
	}

	MachineState getState() const
	{
		return state;
	}

	void setState(MachineState state)
	{
		stats.setState(state);
		this->state = state;
	}
	/**
	 * @brief This function wil do some quick maths!!.. and get u the proper input for the machine
	 * @param parentBuffer is the buffer where the material is coming from, childBuffer is where the material will go, machine will give u information of the machine
	 * @return The proper input for the machine
	 */
	std::map<int,std::pair<int,int>> getMachineInput(Buffer& classChildBuffer,std::map<int, Buffer> classParentBuffer);
	/**
	 * @brief This function will give you the posision of the highest number
	 * @param A list of numbers
	 * @return The position of the highest input
	 */
	int getHighestInput(std::map<int, std::pair<int, int>> &inputs);
	/**
	 * @brief This function will tell u if all the inputs are the same
	 * @param A list of numbers
	 * @return A True if the all the numbers are the same, a false if not
	 */
	bool ArePartsTheSame(std::vector<int> inputs);
	/**
	 * @brief This function will check if the inputs are oke
	 * @param A list of ints
	 * @return A True if the values are oke
	 */
	bool checkInput(int machineINPUT_CAPACITY,int machinePARTS_NEEDED,int PartGonneBeMade,int childMaxBuffer, int childBuffer);
	/**
	 * @brief function prints the statistics from the MachineStatistics stats
	 */
	void printStats();

	bool isReady() const
	{
		return ready;
	}

	void setReady(bool ready)
	{
		this->ready = ready;
	}

	const MachineStatistics& getStats() const
	{
		return stats;
	}

	unsigned long getCurrentAmountOfWork() const
	{
		return currentAmountOfWork;
	}

	void setCurrentAmountOfWork(unsigned long currentAmountOfWork)
	{
		this->currentAmountOfWork = currentAmountOfWork;
	}

	bool isActive() const
	{
		return active;
	}
	void setActive(bool active)
	{
		this->active = active;
	}

private:
	MachineConfig config;
	MachineState state;
	bool ready;
	bool active;
	unsigned long currentAmountOfWork;
	MachineStatistics stats;
};

#endif /* EXE1_LOCALMACHINE_HPP_ */
