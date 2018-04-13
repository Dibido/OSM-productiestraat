/*
 * ConcreteState.cpp
 *
 *  Created on: 26 sep. 2016
 *      Author: stefa
 */

#include <iostream>
#include <random>

#include "ConcreteState.hpp"

Machine* AbstractMachineState::getMachine()
{
	return dynamic_cast<Machine*>(AbstractState::getMachine());
}

// --- STATES --- //

OffState::OffState(Machine* aMachine) :
		AbstractMachineState(aMachine)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
void OffState::doActivity()
{

}
void OffState::entry()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	getMachine()->pc->OK(getMachine()->clock->getSimulationTime(), getMachine()->getMachineId(), MachineState::OFF);
}
void OffState::exit()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
bool OffState::handleEvent(const EventContent& aEV)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	if (aEV.eventType == EventType::TURNON)
	{
		getMachine()->startTime = getMachine()->clock->getSimulationTime();
		const int hoursPerDay = IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY");

		if (!getMachine()->isIsBroken()){
			if (getMachine()->workingMinutes + (hoursPerDay * 60) >= getMachine()->generatedWorkTimeMinutes)
			{
				DEBUG_MSG("machine raakt defect vandaag");
				getMachine()->events->addEvent(
						getMachine()->clock->getSimulationTime()
								+ boost::posix_time::minutes(getMachine()->generatedWorkTimeMinutes - getMachine()->workingMinutes), EventContent
						{ getMachine(), EventType::ISBROKEN });
				getMachine()->workingMinutes = 0;
			}
		}
		getMachine()->currentState->exit();
		getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new InitState(getMachine())));
		getMachine()->currentState->entry();
		return true;
	}
	else if (aEV.eventType == EventType::REPAIRED)
	{
		eventREPAIRED();
		return true;
	}
	return false;
}
OffState::~OffState()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}

InitState::InitState(Machine* aMachine) :
		AbstractMachineState(aMachine)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
void InitState::doActivity()
{

}
void InitState::entry()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	DEBUG_MSG("machine added event: nr: " << getMachine()->config.id);
	getMachine()->events->addEvent(
			getMachine()->clock->getSimulationTime() + boost::posix_time::minutes(getMachine()->config.initializationTime), EventContent
			{ getMachine(), EventType::FINISHEDINIT });
	getMachine()->pc->OK(getMachine()->clock->getSimulationTime(), getMachine()->getMachineId(), MachineState::INIT);
}
void InitState::exit()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
bool InitState::handleEvent(const EventContent& aEV)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);

	if (aEV.eventType == EventType::FINISHEDINIT)
	{
		if (getMachine()->isIsBroken())
		{
			getMachine()->currentState->exit();
			getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new BrokenState(getMachine())));
			getMachine()->currentState->entry();
		}
		else
		{
			getMachine()->currentState->exit();
			getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new OnState(getMachine())));
			getMachine()->currentState->entry();
		}
		return true;
	}
	else if (aEV.eventType == EventType::ISBROKEN)
	{
		eventISBROKEN();
		return true;
	}
	else if (aEV.eventType == EventType::TURNOFF)
	{
		eventTURNOFF();
		return true;
	}
	else if (aEV.eventType == EventType::REPAIRED)
	{
		eventREPAIRED();
		return true;
	}

	return false;
}
InitState::~InitState()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}

OnState::OnState(Machine* aMachine) :
		AbstractMachineState(aMachine)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
void OnState::doActivity()
{

}
void OnState::entry()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	getMachine()->pc->OK(getMachine()->clock->getSimulationTime(), getMachine()->getMachineId(), MachineState::ON);
}
void OnState::exit()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
bool OnState::handleEvent(const EventContent& aEV)
{
	if (aEV.eventType == EventType::STARTWORK)
	{
		DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
		getMachine()->currentState->exit();
		DEBUG_MSG("machine " + std::to_string(getMachine()->getMachineId()) + " state: " + typeid(*getMachine()->currentState).name());
		getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new BusyState(getMachine())));
		getMachine()->currentState->entry();
		return true;
	}
	else if (aEV.eventType == EventType::ISBROKEN)
	{
		eventISBROKEN();
		return true;
	}
	else if (aEV.eventType == EventType::TURNOFF)
	{
		eventTURNOFF();
		return true;
	}
	else if (aEV.eventType == EventType::REPAIRED)
	{
		eventREPAIRED();
		return true;
	}
	return false;
}
OnState::~OnState()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}

BusyState::BusyState(Machine* aMachine) :
		AbstractMachineState(aMachine)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
void BusyState::doActivity()
{

}
void BusyState::entry()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	DEBUG_MSG("machine added event: nr: " << getMachine()->config.id);
	getMachine()->events->addEvent(
			getMachine()->clock->getSimulationTime()
					+ boost::posix_time::milliseconds(
							getMachine()->calculateProcessTime(getMachine()->currentAmountOfWork, getMachine()->config)), EventContent
			{ getMachine(), EventType::FINISHEDWORK });
	getMachine()->pc->OK(getMachine()->clock->getSimulationTime(), getMachine()->getMachineId(), MachineState::BUSY);
}
void BusyState::exit()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
bool BusyState::handleEvent(const EventContent& aEV)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);

	if (aEV.eventType == EventType::FINISHEDWORK)
	{
		getMachine()->currentState->exit();
		getMachine()->pc->finished(getMachine()->calculateOutputParts(getMachine()->currentAmountOfWork, getMachine()->config), getMachine()->clock->getSimulationTime(),
				getMachine()->getMachineId());
		DEBUG_MSG("machine " + std::to_string(getMachine()->getMachineId()) + " state: " + typeid(*getMachine()->currentState).name());
		getMachine()->setCurrentState(std::shared_ptr<AbstractState>(new OnState(getMachine())));
		getMachine()->currentState->entry();
		return true;
	}
	else if (aEV.eventType == EventType::ISBROKEN)
	{
		eventISBROKEN();
		return true;
	}
	else if (aEV.eventType == EventType::TURNOFF)
	{
		eventTURNOFF();
		return true;
	}
	else if (aEV.eventType == EventType::REPAIRED)
	{
		eventREPAIRED();
		return true;
	}
	return false;
}
BusyState::~BusyState()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}

BrokenState::BrokenState(Machine* aMachine) :
		AbstractMachineState(aMachine)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
void BrokenState::doActivity()
{

}
void BrokenState::entry()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);

	const int closingTimeMinutes = ((IniParser::getInstance().getInt("general.MORNING_START_TIME")
			+ IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY")) * 60);
	const int timeThisDayMinutes = (getMachine()->clock->getSimulationTime().total_seconds() / 60) % (24 * 60);
	const int hoursPerDay = IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY");

	if (!getMachine()->isIsBroken())
	{
		static std::mt19937 gen(getMachine()->seed);
		const int repairTime = getMachine()->config.repairTime*60;
		const int stdev = getMachine()->config.STDEV;
		std::normal_distribution<> distribution{repairTime, stdev};
		int repairTimeMinutes = distribution(gen);


		std::ofstream ostream;
		ostream.open("MachineRepairTime.csv", std::ios::out | std::ios::app);
		ostream << getMachine()->config.id << "," << repairTimeMinutes << std::endl;

//		boost::posix_time::time_duration repairedTime = getMachine()->clock->getSimulationTime() + boost::posix_time::minutes(repairTimeMinutes);
////
////		if ((closingTimeMinutes - timeThisDayMinutes) > repairTimeMinutes) // enough time left today
////		{
////			getMachine()->events->addEvent(
////					repairedTime, EventContent
////					{ getMachine(), EventType::REPAIRED });
////		}
//
//		int days = 1;
//		while (repairedTime.minutes() >= closingTimeMinutes)
//		{
//			repairedTime += boost::posix_time::hours(24-hoursPerDay);
//		}
//
//		getMachine()->events->addEvent(
//				repairedTime, EventContent
//				{ getMachine(), EventType::REPAIRED });

//TODO: moet nog generieker worden gemaakt voor lange reparatietijden.
		if ((closingTimeMinutes - timeThisDayMinutes) > repairTimeMinutes) // enough time left today
		{
			getMachine()->events->addEvent(getMachine()->clock->getSimulationTime() + boost::posix_time::minutes(repairTimeMinutes),
					EventContent
					{ getMachine(), EventType::REPAIRED });
		}
		else
		{
			getMachine()->events->addEvent(
					getMachine()->clock->getSimulationTime() + boost::posix_time::minutes(repairTimeMinutes)
							+ boost::posix_time::hours(24 - hoursPerDay), EventContent
					{ getMachine(), EventType::REPAIRED });
		}

	}
	getMachine()->setIsBroken(true);

	//TODO: repairtime based on STDEV
	getMachine()->pc->NOK(getMachine()->clock->getSimulationTime(), getMachine()->getMachineId());
}
void BrokenState::exit()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
bool BrokenState::handleEvent(const EventContent& aEV)
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
	if (aEV.eventType == EventType::TURNOFF)
	{
		eventTURNOFF();
		return true;
	}
	else if (aEV.eventType == EventType::REPAIRED)
	{
		eventREPAIRED();
		return true;
	}
	return false;
}
BrokenState::~BrokenState()
{
	DEBUG_MSG("Machine " << std::to_string(getMachine()->config.id) << " " << __PRETTY_FUNCTION__);
}
