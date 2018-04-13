/*
 * FactoryClock.hpp
 *
 *  Created on: 9 jan. 2018
 *      Author: Stefan
 */

#ifndef EXE1_FACTORYCLOCK_HPP_
#define EXE1_FACTORYCLOCK_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Defines.hpp"

class FactoryClock
{
public:

	static FactoryClock *getInstance()
	{
		static FactoryClock s; return &s;
	}
	FactoryClock(const FactoryClock&) = delete;
	void operator=(const FactoryClock&) = delete;

	const boost::posix_time::time_duration& getSimulationTime() const
	{
		return simulationTime;
	}
	void setSimulationTime(const boost::posix_time::time_duration& simulationTime)
	{
		this->simulationTime = simulationTime;
	}

	bool isRunning() const
	{
		return running;
	}

	void setRunning(bool running = false)
	{
		this->running = running;
	}

private:
	FactoryClock() = default;
	bool running = false;
	boost::posix_time::time_duration simulationTime;
};

#endif /* EXE1_FACTORYCLOCK_HPP_ */
