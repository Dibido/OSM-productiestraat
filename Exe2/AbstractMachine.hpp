/*
 * AbstractMachine.hpp
 *
 *  Created on: 6 dec. 2017
 *      Author: Stefan
 */

#ifndef EXE2_ABSTRACTMACHINE_HPP_
#define EXE2_ABSTRACTMACHINE_HPP_

class MachineConfig;

class AbstractMachine
{
public:
	virtual ~AbstractMachine() {};
	/**
	 * @brief machine will be turned on
	 * @pre machine is in OFF state
	 * @post machine is in INIT state
	 */
	virtual void turnOn() =0;	// =0 is pure virtual
	/**
	 * @brief machine will be turned off
	 * @pre machine is in ON state
	 * @post machine is in OFF state
	 */
	virtual void turnOff() =0;	// =0 is pure virtual
	/**
	 * @brief the machine will be started
	 * @pre machine is in ON state
	 * @post machine is in BUSY state
	 * @param nrOfInputMaterial
	 */
	virtual void startWork(int nrOfInputMaterial) =0;	// =0 is pure virtual
	/**
	 * @brief set the configuration of the system
	 * @pre -
	 * @post configuration of machine is set
	 * @param
	 */
	virtual void setConfig(MachineConfig aConfig) =0;	// =0 is pure virtual
};

#endif /* EXE2_ABSTRACTMACHINE_HPP_ */
