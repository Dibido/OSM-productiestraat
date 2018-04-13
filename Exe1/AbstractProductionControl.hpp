/*
 * AbstractProductionControl.hpp
 *
 *  Created on: 6 dec. 2017
 *      Author: Stefan
 */

#ifndef EXE1_ABSTRACTPRODUCTIONCONTROL_HPP_
#define EXE1_ABSTRACTPRODUCTIONCONTROL_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>
enum struct MachineState;

class AbstractProductionControl
{
public:
	virtual ~AbstractProductionControl() {};
	/**
	 * @brief the machine finished a task
	 * @param nrOfOutput nr of outputmaterial of machine
	 * @param time used to sync time between machines
	 * @param machineId machineId
	 */
	virtual void finished(int nrOfOutput, boost::posix_time::time_duration time, int machineId) =0;	// =0 is pure virtual
	/**
	 * @brief will be called by machine if machine is not broken
	 * @param time current time now.
	 * @param machineId id of the machine
	 * @param currentState state of the machine after OK
	 * @pre -
	 * @post -
	 */
	virtual void OK(boost::posix_time::time_duration time, int machineId, MachineState currentState) =0;	// =0 is pure virtual
	/**
	 * @brief will be called by machine if machine is broken
	 * @param time current time now.
	 * @param machineId id of the machine
	 * @pre -
	 * @post -
	 */
	virtual void NOK(boost::posix_time::time_duration time, int machineId) =0;	// =0 is pure virtual

//	/**
//	 * @brief Function for the machines to call to log data
//	 */
//	virtual static void log(std::string log_data) =0;	// =0 is pure virtual
};



#endif /* EXE1_ABSTRACTPRODUCTIONCONTROL_HPP_ */
