/*
 * ProxyProductionControl.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Stefan
 */

#include "ProxyProductionControl.hpp"

ProxyProductionControl::ProxyProductionControl(ProductionControl* pc,
		// cppcheck-suppress passedByValue
		ControlNetworkHandlerPtr cnhPtr) :
		machines(), events(), clock(this), pc(pc), cnhPtr(cnhPtr)
{
	//Set input file
	IniParser::getInstance().setFile("../../Exe2/"
			"configMachineNetwork.ini");
}

void ProxyProductionControl::makeMachine(MachineConfig& config)
{
	Machine machine = Machine(this, config, &events, &clock);
	machines.insert(std::pair<int, Machine>(config.id, (machine)));
	machines.at(config.id).init();

	if (std::ifstream("MachineRepairTime.csv")) {
		if (remove("MachineRepairTime.csv") != 0) {
			throw std::runtime_error("Error deleting previous log file");
		}
	}

}

ProxyProductionControl::~ProxyProductionControl()
{
}

void ProxyProductionControl::init()
{
	//start simulation
	DEBUG_MSG(" !.!.!.start simulation.!.!.!");

#define THREADING 2 // 0 = no threading  1 = separate machine threading  2 = all machines threading
#if THREADING == 0
	clock.resume();
	while (clock.isSimulationRunning())
	{
		for (auto& it : boost::adaptors::reverse(machines))
		{
			it.second.runMachine();
		}
	}
#elif THREADING == 1
	for (auto& it : boost::adaptors::reverse(machines))
	{
		it.second.startMachine();
	}
	clock.resume();
#else
	std::thread([this]()
	{
		while (clock.isSimulationRunning())
		{
			std::this_thread::sleep_for (std::chrono::nanoseconds(1));
			for (auto& it : boost::adaptors::reverse(machines))
			{
				it.second.runMachine();
			}
		}
		DEBUG_MSG("PPC tread stopped.");
		simulationStopped(clock.getSimulationTime());
	}).detach();
	clock.pause();
#endif
	return;
}

void ProxyProductionControl::finished(int nrOfOutput,
		boost::posix_time::time_duration time, int machineId)
{

	clock.pause(); //TODO: moet de machine zelf gaan doen.
	DEBUG_MSG(__PRETTY_FUNCTION__ << " machineId: " << machineId);

#if NETWORK > 0
	cnhPtr->finished(nrOfOutput, time, machineId);
#else
	pc->finished(nrOfOutput, time, machineId);
#endif
}

void ProxyProductionControl::OK(boost::posix_time::time_duration time,
		int machineId, MachineState currentState)
{
	clock.pause();
	DEBUG_MSG(
			__PRETTY_FUNCTION__ << " machineId: " << machineId << " currentState: " << std::to_string(static_cast<int>(currentState)));

#if NETWORK > 0
	cnhPtr->OK(time, machineId, currentState);
#else
	pc->OK(time, machineId, currentState);
#endif
}

void ProxyProductionControl::NOK(boost::posix_time::time_duration time,
		int machineId)
{
	clock.pause();
	DEBUG_MSG(__PRETTY_FUNCTION__ << " machineId: " << machineId);

#if NETWORK > 0
	cnhPtr->NOK(time, machineId);
#else
	pc->NOK(time, machineId);
#endif
}

void ProxyProductionControl::log(std::string log_data)
{
#if NETWORK > 0
	cnhPtr->log(log_data);
#else
	pc->log(log_data);
#endif
}

void ProxyProductionControl::simulationStopped(boost::posix_time::time_duration time)
{
#if NETWORK > 0
	cnhPtr->simulationStopped(time);
#else
	pc->simulationStopped(time);
#endif
}
