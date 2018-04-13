/*
 * ProductionControl.hpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE1_PRODUCTIONCONTROL_HPP_
#define EXE1_PRODUCTIONCONTROL_HPP_

#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <map>
#include <string>


#include "Logger/Log_to_file.hpp"

#include "Logger/Queued_logger.hpp"
#include "IniParser/IniParser.hpp"
#include "../Exe2/Clock.hpp"
#include "ProxyMachine.hpp"
#include "../Exe2/MachineState.hpp"
#include "../Exe2/MachineCalculations.hpp"
#include "Buffer.hpp"
#include "LocalMachine.hpp"
#include "../Exe2/MachineConfig.hpp"
#include "LoadConfiguration.hpp"
#include "AbstractProductionControl.hpp"
#include "Network/machineNetworkHandler.hpp"
#include "ProxyClock.hpp"
#include "FactoryClock.hpp"
#include "ConfigStructs.hpp"

#include "../Exe2/ProxyProductionControl.hpp"

class ProxyMachine;
class MachineConfig;
class ProxyProductionControl;
class ProxyClock;

/**
 * @brief simple ProductionControl which makes machines.
 */
class ProductionControl : public AbstractProductionControl
{
public:
	explicit ProductionControl(MachineNetworkHandlerPtr mnhPtr = nullptr);

	/**
	 * @brief init function of ProductionControl
	 * @param configFile path to file with configuration of machines
	 */
	void init(const std::string& configFile);
	/**
	 * @brief init function of ProductionControl without configfile
	 */
	void init();
	/**
	 * @brief function starts the simulation.
	 */
	void start();
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
	 * @brief function is called by proxyproductioncontrol when the simulation is stopped. prints statistics of machines
	 * @param time current time now
	 */
	void simulationStopped(boost::posix_time::time_duration time);

	/**
	 * @brief function will produce a batch of products
	 * @param batch_size nr of products in batch
	 * @return nr of products that are made
	 */
	unsigned long produce_batch(unsigned long batch_size);
	/**
	 * @brief checks if batch is finished
	 * @return returns true if batch is finished
	 */
	bool batchFinished();
	/**
	 * @brief This function will give u all the first buffers from the assembly line
	 * @return A map with the id's and the number of what value of the machine this value is found (Not used right now)
	 */
	std::map<unsigned long,unsigned long> getFirstBuffers();
	/**
	 * @brief function updates the machines with the new config.
	 * @param productionLineConfig struct with the configs of machines and buffers
	 */
	void updateProductionLineConfig(const ProductionLineConfig& productionLineConfig);
	/**
	 * @brief Function for the machines to call to log data
	 */
	static void log(std::string log_data);
	/**
	 * @brief This function will check what buffers are the first once and need to be filled
	 * @param -
	 * @pre -
	 * @post -
	 * @return Its will return a map with as first value the buffer id and the second one is a values for one part to be build in the production line
	 */
	std::map<unsigned long, unsigned long> calculateFirstBufferSize();
	virtual ~ProductionControl();

private:
	std::map<int, ProxyMachine> machines;
	std::map<int, LocalMachine> localMachines;
	std::map<int, Buffer> buffers;
	ProxyProductionControl* ppc;
	MachineNetworkHandlerPtr mnhPtr;
	ProxyClock* pClock;
	/**
	 * @brief function loops through machines and starts if possible
	 */
	void checkMachines();
	/**
	 * @brief This function will calculate the amount needed for one part
	 * @param A stack with all the Parts needed for every machine from the start machine till the last machine
	 * @pre -
	 * @post -
	 * @return - The amount the first buffer needs for the whole line to make one product
	 */
	unsigned long getPartsNeededForOnePart(std::stack<unsigned long> partsNeededForAllMachines);
	/**
	 * @brief This function will check if this is the last buffer of the line
	 * @param The id of the buffer u want to know if its the last one
	 * @pre -
	 * @post -
	 * @return True if its the last one
	 */
	bool doesBufferHaveParent(unsigned long bufferId);
	/**
	 * @brief This function will give u the matching machine for this buffer id
	 * @param The buffer id ware u want to know the maching machien for
	 * @pre -
	 * @post -
	 * @return A vector with 2 values the first one will give the Machine id and the second one will give u the value of which parent id this buffer is
	 */
	std::vector<unsigned long> getMachineChild(unsigned long bufferId);
	/**
	 * @brief contains loop which checks if machines are ready
	 * @returns if all machines are ready
	 */
	void machinesReady();
};

#endif /* EXE1_PRODUCTIONCONTROL_HPP_ */
