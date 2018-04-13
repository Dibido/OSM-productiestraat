/*
 * Clock.cpp
 *
 *  Created on: 20 nov. 2017
 *      Author: Stefan
 */

#include "Clock.hpp"
#include "ProxyProductionControl.hpp"

Clock::Clock(ProxyProductionControl* ppc)
	: simulationTime(0,0,0), paused(true), simulationRunning(false), ppc(ppc)
{
}

Clock::~Clock()
{
}

void Clock::startSimulation()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	simulationRunning = true;
	ppc->init();
}

void Clock::pause()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	paused = true;
}

void Clock::stopSimulation()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	simulationRunning = false;
	DEBUG_MSG("Simulation Stopped. time: " + std::to_string(simulationTime.total_seconds() / 60));
}

void Clock::resume()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	paused = false;
}
