/*
 * AbstractState.cpp
 *
 *  Created on: 14 dec. 2017
 *      Author: Stefan
 */
#include "AbstractState.hpp"
#include "Machine.hpp"

void AbstractState::eventTURNOFF()
{
	getMachine()->workingMinutes += (getMachine()->clock->getSimulationTime() - getMachine()->startTime).total_seconds() / 60;
	DEBUG_MSG("workingMinutes: " << getMachine()->workingMinutes);

	getMachine()->currentState->exit();
	getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new OffState(getMachine())));
	getMachine()->currentState->entry();
}

void AbstractState::eventREPAIRED()
{
	getMachine()->setIsBroken(false);

	getMachine()->generatedWorkTimeMinutes = getMachine()->generateWorkTimeMinutes();
	getMachine()->workingMinutes = 0;

	const int hoursPerDay = IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY");
	getMachine()->startTime = getMachine()->clock->getSimulationTime();
	if (getMachine()->workingMinutes + (hoursPerDay * 60) >= getMachine()->generatedWorkTimeMinutes)
	{
		DEBUG_MSG("machine raakt defect vandaag");
		getMachine()->events->addEvent(getMachine()->clock->getSimulationTime() + boost::posix_time::minutes(getMachine()->generatedWorkTimeMinutes - getMachine()->workingMinutes), EventContent
		{ getMachine(), EventType::ISBROKEN });
		getMachine()->workingMinutes = 0;
	}

	getMachine()->startTime = getMachine()->clock->getSimulationTime();
	getMachine()->currentState->exit();
	getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new InitState(getMachine())));
	getMachine()->currentState->entry();
}

void AbstractState::eventISBROKEN()
{
	if (!getMachine()->isIsBroken())
	{
		getMachine()->brokenSinceTime = getMachine()->clock->getSimulationTime();
	}

	getMachine()->currentState->exit();
	getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new BrokenState(getMachine())));
	getMachine()->currentState->entry();
}
