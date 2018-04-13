/*
 * Machine.hpp
 *
 *  Created on: 17 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_MACHINE_HPP_
#define EXE2_MACHINE_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <memory>
#include <thread>
#include <random>

#include "ProxyProductionControl.hpp"
#include "Clock.hpp"
#include "Events.hpp"
#include "ConcreteState.hpp"
#include "../Exe1/IniParser/IniParser.hpp"
#include "Defines.hpp"
#include "MachineCalculations.hpp"
#include "MachineConfig.hpp"
#include "EventContent.hpp"
#include "AbstractMachine.hpp"

class AbstractState;
class Clock;
class Events;

class ProxyProductionControl;


/**
 * @brief this is the machine. the machine has a state-machine and a thread that processes events.
 */
class Machine : public MachineCalculations, public AbstractMachine
{
	friend class AbstractState;
	friend class OffState;
	friend class InitState;
	friend class OnState;
	friend class BusyState;
	friend class BrokenState;
public:
	Machine(ProxyProductionControl* aPc, MachineConfig& aConfig, Events* anEvents, Clock* aClock); //TODO: bufferids moeten in configStruct erbij
	Machine(const Machine& obj);
	Machine& operator=(const Machine& obj);
	/**
	 * @brief function for initializing a machine
	 * @post TURNON/TURNOFF/FINISHEDSIMULATION events are generated
	 */
	void init();
	/**
	 * @brief machine will be turned on
	 * @pre machine is in OFF state
	 * @post machine is in INIT state
	 */
	void turnOn();
	/**
	 * @brief machine will be turned off
	 * @pre machine is in ON state
	 * @post machine is in OFF state
	 */
	void turnOff();
	/**
	 * @brief the machine will be started
	 * @pre machine is in ON state
	 * @post machine is in BUSY state
	 * @param nrOfInputMaterial
	 */
	void startWork(int nrOfInputMaterial);
	/**
	 * @brief set the configuration of the system
	 * @pre -
	 * @post configuration of machine is set
	 * @param
	 */
	void setConfig(MachineConfig aConfig);
	/**
	 * @brief function starts machine thread, must be called to start simulation.
	 * @pre simulation clock is running
	 * @post thread runmachine() is started
	 */
	void startMachine();
	/**
	 * @brief function runs in thread and handles events
	 * @pre -
	 * @post simulation is finished
	 */
	void runMachine();
	/**
	 * @brief set the state of the machine
	 * @pre machine is in a state
	 * @post machine is in the given state
	 * @param currentState
	 */
	void setCurrentState(const std::shared_ptr<AbstractState>& currentState);
	/**
	 * @brief destructor
	 */
	virtual ~Machine();



	bool isIsBroken() const
	{
		return isBroken;
	}
	ProxyProductionControl* getProductionControl()
	{
		return pc;
	}
	int getMachineId() const
	{
		return config.id;
	}
	Events* getEvents()
	{
		return events;
	}
	Clock* getClock()
	{
		return clock;
	}
	const MachineConfig& getConfig() const
	{
		return config;
	}
	void setIsBroken(bool isBroken)
	{
		this->isBroken = isBroken;
	}
	std::shared_ptr<AbstractState>& getCurrentState()
	{
		return currentState;
	}

private:
	ProxyProductionControl* pc;
	MachineConfig config;
	Events* events;
	Clock* clock;
	int currentAmountOfWork;
	bool isBroken;
	std::shared_ptr<AbstractState> currentState;
	boost::posix_time::time_duration startTime;
	int workingMinutes;
	boost::posix_time::time_duration brokenSinceTime;
	int totalBrokenTime;
	unsigned int generatedWorkTimeMinutes;
	unsigned long seed;

	/**
	 * @brief function runs in thread and handles events
	 * @pre -
	 * @post simulation is finished
	 */
	void runMachineThread();
	/**
	 * @brief function calculates the time that the machine runs based on MTBF
	 * @return the calculated working time in minutes
	 */
	unsigned int generateWorkTimeMinutes();
};

#endif /* EXE1_MACHINE_HPP_ */
