/*
 * ProxyMachine.cpp
 *
 *  Created on: 4 dec. 2017
 *      Author: Stefan
 */

#include "ProxyMachine.hpp"

// cppcheck-suppress passedByValue
ProxyMachine::ProxyMachine(MachineConfig aConfig, MachineNetworkHandlerPtr mnhPtr, ProxyProductionControl* ppc)
: ppc(ppc), mnhPtr(mnhPtr), id(aConfig.id)
{
#if NETWORK > 0
	mnhPtr->createMachine(aConfig);
#else
	ppc->makeMachine(aConfig);
#endif
}

void ProxyMachine::turnOn()
{
#if NETWORK > 0
	mnhPtr->turnOn(id);
#else
	ppc->getMachine(id)->turnOn();
#endif
}

void ProxyMachine::turnOff()
{
#if NETWORK > 0
	mnhPtr->turnOff(id);
#else
	ppc->getMachine(id)->turnOff();
#endif
}

void ProxyMachine::startWork(int nrOfInputMaterial)
{
#if NETWORK > 0
	mnhPtr->startWorking(nrOfInputMaterial, id);
#else
	ppc->getMachine(id)->startWork(nrOfInputMaterial);
#endif

}

void ProxyMachine::setConfig(MachineConfig aConfig)
{
#if NETWORK > 0
	mnhPtr->setConfig(aConfig, id);
#else
	id = aConfig.id;
		ppc->getMachine(id)->setConfig(aConfig);
#endif

}

ProxyMachine::~ProxyMachine()
{
}

