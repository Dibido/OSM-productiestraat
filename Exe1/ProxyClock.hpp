/*
 * ProxyClock.hpp
 *
 *  Created on: 6 dec. 2017
 *      Author: Stefan
 */

#ifndef EXE1_PROXYCLOCK_HPP_
#define EXE1_PROXYCLOCK_HPP_

#include "Network/machineNetworkHandler.hpp"


class Clock;

class ProxyClock
{
public:
	ProxyClock(Clock* aClock = nullptr, MachineNetworkHandlerPtr mnhPtr = nullptr);
	virtual ~ProxyClock();
	/**
	 * @brief start the simulation run
	 * @pre -
	 * @post simulation is running
	 */
	void startSimulation();
	/**
	 * @brief stop the simulation run
	 * @pre simulation is running
	 * @post simulation is stopped
	 */
	void stopSimulation();
	/**
	 * @brief pause the simulation
	 * @pre simulation is running
	 * @post simulation is paused
	 */
	void pause();
	/**
	 * @brief resume the simulation if paused
	 * @pre simulation is stopped
	 * @post simulation is resumed
	 */
	void resume();
private:
	Clock* clock;
	MachineNetworkHandlerPtr mnhPtr;
};

#endif /* EXE1_PROXYCLOCK_HPP_ */
