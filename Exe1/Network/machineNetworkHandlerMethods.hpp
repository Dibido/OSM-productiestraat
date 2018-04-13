/*
 * machineNetworkHandlerMethods.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */
#ifndef EXE1_NETWORK_PROXYMACHINEMETHODS_HPP_
#define EXE1_NETWORK_PROXYMACHINEMETHODS_HPP

#include <boost/property_tree/ptree_fwd.hpp>
#include "../../Exe2/MachineConfig.hpp"

using boost::property_tree::ptree;

/**
 * @brief Virtual methods to implement the machineNetwork stack
 */
class machineNetworkHandlerMethods {
public:
	inline machineNetworkHandlerMethods(){};
	inline virtual ~machineNetworkHandlerMethods(){};
	virtual void createMachine(MachineConfig config) = 0;
	virtual void setConfig(MachineConfig config, int machineId) = 0;
	virtual void turnOn(int machineId) = 0;
	virtual void turnOff(int machineId) = 0;
	virtual void getStatus(int machineId) = 0;
	virtual void startWorking(int nrOfProducts, int machineId) = 0;
	virtual void startClock() = 0;
	virtual void resumeClock() = 0;
	virtual void stopClock() = 0;
};

#endif /* EXE1_NETWORK_PROXYMACHINEMETHODS_HPP_ */
