/*
 * ProxyProductionControl.hpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_PROXYPRODUCTIONCONTROL_HPP_
#define EXE2_PROXYPRODUCTIONCONTROL_HPP_

#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <map>
#include <string>

#include <fstream>
#include <mutex>
#include <iostream>

#include "../Exe1/IniParser/IniParser.hpp"
#include "Clock.hpp"
#include "Events.hpp"
#include "Machine.hpp"
#include "MachineState.hpp"
#include "MachineCalculations.hpp"
#include "MachineConfig.hpp"
#include "../Exe1/Network/controlNetworkHandler.hpp"
#include "../Exe1/AbstractProductionControl.hpp"
#include "../Exe1/ProductionControl.hpp"

class Machine;
class MachineConfig;
class ProductionControl;

class controlNetworkHandler;
typedef std::shared_ptr<controlNetworkHandler> ControlNetworkHandlerPtr;

/**
 * @brief ProxyProductionControl which handles communication with ProductionControl
 */
class ProxyProductionControl : public AbstractProductionControl
{
public:
	ProxyProductionControl(ProductionControl* pc, ControlNetworkHandlerPtr cnhPtr);
	virtual ~ProxyProductionControl();

	/**
	 * @brief function starts simulation, and loops through machines
	 * @post simulation is finished
	 */
	void init();
	/**
	 * @brief the machine finished a task
	 * @param nrOfOutput nr of outputmaterial of machine
	 * @param time used to sync time between machines
	 * @param machineId machineId
	 */
	void finished(int nrOfOutput, boost::posix_time::time_duration time, int machineId);
	/**
	 * @brief will be called by machine if machine is not broken
	 * @param time current time now.
	 * @param machineId id of the machine
	 * @param currentState state of the machine after OK
	 * @pre -
	 * @post -
	 */
	void OK(boost::posix_time::time_duration time, int machineId, MachineState currentState);
	/**
	 * @brief will be called by machine if machine is broken
	 * @param time current time now.
	 * @param machineId id of the machine
	 * @pre -
	 * @post -
	 */
	void NOK(boost::posix_time::time_duration time, int machineId);

	/**
	 * @brief will be called by proxyproductioncontrol or machine at when the simulation is finished
	 * @param time current time now.
	 */
	void simulationStopped(boost::posix_time::time_duration time);

	/**
	 * @brief Function for the machines to call to log data
	 */
	void log(std::string log_data);

	/**
	 * @brief function makes machines and puts them in map<> machines
	 * @param config config of the machines
	 */
	void makeMachine(MachineConfig& config);

	Machine* getMachine(int id)
	{
		return &machines.at(id);
	}

	Clock& getClock()
	{
		return clock;
	}

private:
	std::map<int, Machine> machines;
	Events events;
	Clock clock;
	ProductionControl* pc;
	ControlNetworkHandlerPtr cnhPtr;
};

#endif /* EXE1_PRODUCTIONCONTROL_HPP_ */
