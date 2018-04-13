/*
 * ProductionScheduling.cpp
 *
 *  Created on: Dec 19, 2017
 *      Author: Kevin Taartmans
 */

#include "ProductionScheduling.hpp"
#include <iostream>

ProductionScheduling::ProductionScheduling()
: mnhPtr(std::make_shared<machineNetworkHandler>(nullptr)), pc(mnhPtr)
{
	pc.init();
}

ProductionScheduling::~ProductionScheduling()
{
}

void ProductionScheduling::processOrder(const std::vector<ProductionLineConfig> ProductionLineConfigVector)
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	int amountCheap = ProductionLineConfigVector.at(1).totalAmountToProduce;
	int amountExpensive = ProductionLineConfigVector.at(0).totalAmountToProduce;

	while(amountCheap > 0 || amountExpensive > 0)
	{
		int batchSizeCheap;
		int batchSizeExpensive;

		batchSizeCheap = ProductionLineConfigVector.at(1).batchSize;
		batchSizeExpensive = ProductionLineConfigVector.at(0).batchSize;

		if(amountCheap < batchSizeCheap && amountCheap > 0){
			batchSizeCheap=amountCheap;//no full cheap batch left anymore
		}
		if(amountExpensive < batchSizeExpensive && amountExpensive > 0){
			batchSizeExpensive=amountExpensive;//no full expensive batch left anymore
		}

		if(amountCheap > 0 && amountExpensive > 0)
		{
			fillQueue(batchSizeCheap,ProductionLineConfigVector.at(1));
			amountCheap -=batchSizeCheap;
			fillQueue(batchSizeExpensive,ProductionLineConfigVector.at(0));
			amountExpensive -=batchSizeExpensive;
		}
		else if(amountCheap == 0 && amountExpensive > 0)//only expensive tables left
		{
			fillQueue(batchSizeExpensive,ProductionLineConfigVector.at(0));
			amountExpensive -=batchSizeExpensive;
		}
		else if(amountCheap > 0 && amountExpensive == 0)//only cheap tables left
		{
			fillQueue(batchSizeCheap,ProductionLineConfigVector.at(1));
			amountCheap -=batchSizeCheap;
		}
	}

	ProductionLineConfig lastBatch;
	lastBatch.batchSize = batchesToProduce.front().batchSize;
	lastBatch.bcm = batchesToProduce.front().bcm;
	lastBatch.mcm = batchesToProduce.front().mcm;

	while(!batchesToProduce.empty() && FactoryClock::getInstance()->isRunning())
	{
		// TODO: wat als twee productielijnen dezelfde aantal machines, buffers en batchsize hebben?....
		if(batchesToProduce.front().number_of_buffers != lastBatch.number_of_buffers ||
				batchesToProduce.front().number_of_machines != lastBatch.number_of_machines ||
				batchesToProduce.front().batchSize != lastBatch.batchSize)
		{
			pc.updateProductionLineConfig(batchesToProduce.front());

		}

		pc.produce_batch(batchesToProduce.front().batchSize);

		lastBatch.batchSize = batchesToProduce.front().batchSize;
		lastBatch.bcm = batchesToProduce.front().bcm;
		lastBatch.mcm = batchesToProduce.front().mcm;

		DEBUG_MSG("Number of badges: "<<batchesToProduce.size());
		DEBUG_MSG("Number of buffers: "<<batchesToProduce.front().number_of_buffers);
		DEBUG_MSG("Number of buffers lastBatch: "<<lastBatch.number_of_buffers);
		DEBUG_MSG("Number of machines: "<<batchesToProduce.front().number_of_machines);
		DEBUG_MSG("Number of machines lastBatch: "<<lastBatch.number_of_machines);
		DEBUG_MSG("BatchSize: "<<batchesToProduce.front().batchSize);
		DEBUG_MSG("BatchSize lastBatch: "<<lastBatch.batchSize);

		batchesToProduce.pop();

	}
}

//cppcheck-suppress functionStatic
void ProductionScheduling::fillQueue(int totalNrPerTypeProduct, ProductionLineConfig config)
{
	ProductionLineConfig newProductionLineConfig;
	newProductionLineConfig.batchSize = totalNrPerTypeProduct;
	newProductionLineConfig.bcm = config.bcm;
	newProductionLineConfig.mcm = config.mcm;

	batchesToProduce.push(newProductionLineConfig);
}
