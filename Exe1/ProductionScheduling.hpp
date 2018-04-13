/*
 * ProductionScheduling.hpp
 *
 *  Created on: Dec 19, 2017
 *      Author: Kevin Taartmans
 */

#ifndef EXE1_PRODUCTIONSCHEDULING_HPP_
#define EXE1_PRODUCTIONSCHEDULING_HPP_

#include <queue>
#include <vector>

#include "ConfigStructs.hpp"
#include "ProductionControl.hpp"

/*
 * @brief This class creates and fills a queue with batches that need to be produced
 */
class ProductionScheduling
{
public:
	ProductionScheduling();
	virtual ~ProductionScheduling();

	/*
	 * @brief Calls fillsQueue with batchSize and configurations, calls setProductieStraat if the configuration has changed, calls produceBatch for each batch in the queue
	 * @param nrCheap, the number of cheap tables to be produced
	 * @param nrExpensive , the number of expensive tables to be produced
	 * @param ProductionLineConfigVector, vector with batch size, machine configurations and buffer configurations recieved from the Factory class
	 */
	void processOrder(const std::vector<ProductionLineConfig> configVector);

	/*
	 * @brief Fills the queue
	 * @param totalNrPerTypeProduct, the total number of products to be produced for all the types of to produced tables
	 * @param ProductionLineConfigVector, vector with batch size, machine configurations and buffer configurations recieved from the processOrder function
	 */
	void fillQueue(int totalNrPerTypeProduct, ProductionLineConfig config);

private:

	std::queue<ProductionLineConfig> batchesToProduce;
	MachineNetworkHandlerPtr mnhPtr;
	ProductionControl pc;
};

#endif /* EXE1_PRODUCTIONSCHEDULING_HPP_ */
