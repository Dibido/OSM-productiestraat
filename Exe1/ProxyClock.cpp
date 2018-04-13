/*
 * ProxyClock.cpp
 *
 *  Created on: 6 dec. 2017
 *      Author: Stefan
 */

#include "ProxyClock.hpp"
#include "../Exe2/Clock.hpp"

// cppcheck-suppress passedByValue
ProxyClock::ProxyClock(Clock* aClock, MachineNetworkHandlerPtr mnhPtr)
 : clock(aClock), mnhPtr(mnhPtr)
{

}

ProxyClock::~ProxyClock()
{

}

void ProxyClock::startSimulation()
{
#if NETWORK > 0
	mnhPtr->startClock();
#else
	clock->startSimulation();
#endif
}

void ProxyClock::stopSimulation()
{
#if NETWORK > 0
	mnhPtr->stopClock();
#else
	clock->stopSimulation();
#endif
}

void ProxyClock::pause()
{
#if NETWORK > 0
	mnhPtr->pauseClock();
#else
	clock->pause();
#endif
}

void ProxyClock::resume()
{
#if NETWORK > 0
	mnhPtr->resumeClock();
#else
	clock->resume();
#endif
}
