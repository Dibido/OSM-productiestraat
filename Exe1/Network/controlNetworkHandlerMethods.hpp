/*
 * controlNetworkHandlerMethods.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */

#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <string>

#include "../../Exe2/MachineState.hpp"

using namespace boost::posix_time;

#ifndef EXE1_NETWORK_PROXYCONTROLMETHODS_HPP_
#define EXE1_NETWORK_PROXYCONTROLMETHODS_HPP_

/**
 * @brief Virtual methods to implement the controlNetwork stack
 */
class controlNetworkHandlerMethods {
public:
	inline controlNetworkHandlerMethods(){};
	inline virtual ~controlNetworkHandlerMethods(){};
	virtual void OK(time_duration time, int machineId, MachineState currentState) = 0;
	virtual void NOK(time_duration time, int machineId) = 0;
	virtual void log(const std::string& text) = 0;
	virtual void finished(int nrOfOutput, time_duration time,
			int machineId) = 0;
	virtual void simulationStopped(time_duration time) = 0;
	virtual void machineBroken(time_duration time, int machineId) = 0;
};

#endif /* EXE1_NETWORK_PROXYCONTROLMETHODS_HPP_ */
