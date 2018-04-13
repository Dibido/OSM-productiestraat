/*
 * Clock.hpp
 *
 *  Created on: 20 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_CLOCK_HPP_
#define EXE2_CLOCK_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Defines.hpp"

class ProxyProductionControl;

/**
 * @brief class that keeps the time
 */
class Clock
{
public:
	explicit Clock(ProxyProductionControl* ppc = nullptr);
	virtual ~Clock();

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


	const boost::posix_time::time_duration& getSimulationTime() const
	{
		return simulationTime;
	}
	void setSimulationTime(const boost::posix_time::time_duration& simulationTime)
	{
		this->simulationTime = simulationTime;
	}

	bool isSimulationRunning() const
	{
		return simulationRunning;
	}

	bool isPaused() const
	{
		return paused;
	}

private:
	boost::posix_time::time_duration simulationTime;

	bool paused;
	bool simulationRunning;
	ProxyProductionControl* ppc;
};

#endif /* EXE2_CLOCK_HPP_ */
