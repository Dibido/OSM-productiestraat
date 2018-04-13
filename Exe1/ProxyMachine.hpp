/*
 * ProxyMachine.hpp
 *
 *  Created on: 4 dec. 2017
 *      Author: Stefan
 */

#ifndef EXE1_PROXYMACHINE_HPP_
#define EXE1_PROXYMACHINE_HPP_

#include "Defines.hpp"
#include "../Exe2/MachineConfig.hpp"
#include "../Exe2/ProxyProductionControl.hpp"
#include "Network/machineNetworkHandler.hpp"
#include "../Exe2/AbstractMachine.hpp"

class machineNetworkHandler;
typedef std::shared_ptr<machineNetworkHandler> MachineNetworkHandlerPtr;

class ProductionControl;

class ProxyProductionControl;

/**
 * @brief proxy: functions are implemented in Machine class
 */
class ProxyMachine : public AbstractMachine
{
public:
	ProxyMachine(MachineConfig aConfig, MachineNetworkHandlerPtr mnhPtr, ProxyProductionControl* ppc);
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
	virtual ~ProxyMachine();
private:
	ProxyProductionControl* ppc;
	MachineNetworkHandlerPtr mnhPtr;
	int id;
};

#endif /* EXE1_PROXYMACHINE_HPP_ */
