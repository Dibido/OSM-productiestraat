/*
 * MachineCalculations.cpp
 *
 *  Created on: 28 nov. 2017
 *      Author: Stefan
 */

#include "MachineCalculations.hpp"

MachineCalculations::MachineCalculations()
{
}

/* static */ int MachineCalculations::calculateOutputParts(int inputAmount, const MachineConfig& aConfig)
{
	int parts = (inputAmount / aConfig.partsNeeded.at(0));
	return parts;
}

int MachineCalculations::calculateProcessTime(int inputAmount, const MachineConfig& aConfig)
{
	int time = (aConfig.productionTime) + (aConfig.dryingTime * 60 * 1000);
	return time;
}


MachineCalculations::~MachineCalculations()
{
}
