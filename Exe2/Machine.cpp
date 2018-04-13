/*
 * Machine.cpp
 *
 *  Created on: 17 nov. 2017
 *      Author: Stefan
 */

#include "Machine.hpp"

Machine::Machine(ProxyProductionControl* aPc, MachineConfig& aConfig,
		Events* anEvents, Clock* aClock) :
		pc(aPc), config(aConfig), events(anEvents), clock(aClock), currentAmountOfWork(
				0), isBroken(false), currentState(nullptr), startTime(
				0, 0, 0), workingMinutes(0), brokenSinceTime(0, 0, 0), totalBrokenTime(
				0), generatedWorkTimeMinutes(0), seed(0)
{
}

Machine::Machine(const Machine& obj) :
		pc(obj.pc), config(obj.config), events(obj.events), clock(obj.clock), currentAmountOfWork(
				obj.currentAmountOfWork), isBroken(obj.isBroken), currentState(
				obj.currentState), startTime(obj.startTime), workingMinutes(
				obj.workingMinutes), brokenSinceTime(obj.brokenSinceTime), totalBrokenTime(
				obj.totalBrokenTime), generatedWorkTimeMinutes(obj.generatedWorkTimeMinutes),
				seed(obj.seed)
{
}

Machine& Machine::operator =(const Machine& obj)
{
	if (this != &obj)
	{
		pc = obj.pc;
		config = obj.config;
		events = obj.events;
		clock = obj.clock;
		currentAmountOfWork = obj.currentAmountOfWork;
		isBroken = obj.isBroken;
		currentState = obj.currentState;
		startTime = obj.startTime;
		workingMinutes = obj.workingMinutes;
		brokenSinceTime = obj.brokenSinceTime;
		totalBrokenTime = obj.totalBrokenTime;
		generatedWorkTimeMinutes = obj.generatedWorkTimeMinutes;
		seed = obj.seed;
	}
	return *this;
}

Machine::~Machine()
{
}

void Machine::startWork(int nrOfInputMaterial)
{
	DEBUG_MSG(
			__PRETTY_FUNCTION__ << " id: " + std::to_string(getConfig().id) + " startWork input: " << std::to_string(nrOfInputMaterial));
	if (!isIsBroken())
	{
		if (nrOfInputMaterial > config.inputCapacity.front()
				|| (nrOfInputMaterial % config.partsNeeded.front()) != 0)
		{
			throw std::invalid_argument("Machine Overflow");
		}
		currentAmountOfWork = nrOfInputMaterial;
		events->addEvent(clock->getSimulationTime(), EventContent
		{ this, EventType::STARTWORK });
		DEBUG_MSG("machine added event: nr: " << config.id);
	}
	else
	{
		getProductionControl()->NOK(clock->getSimulationTime(), getMachineId());
	}
}

// cppcheck-suppress passedByValue
void Machine::setConfig(MachineConfig aConfig)
{
	// check if machine is in 1 on of the specified states...
	if (typeid(*currentState).name() == typeid(OffState).name()
			|| typeid(*currentState).name() == typeid(OnState).name()
			|| typeid(*currentState).name() == typeid(InitState).name())
	{
		config = aConfig;
		this->currentState->exit();
		setCurrentState(std::shared_ptr<AbstractState>(new InitState(this)));
		this->currentState->entry();
	}
	if(typeid(*currentState).name() == typeid(BrokenState).name())
	{
		config = aConfig;
		this->currentState->exit();
		setCurrentState(std::shared_ptr<AbstractState>(new InitState(this)));
		this->currentState->entry();

	}
}

void Machine::startMachine()
{
	std::thread([this]()
	{
		runMachineThread();
	}).detach();
}

void Machine::init()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	//simulation parameters
	seed = IniParser::getInstance().getInt("general.SEED");
	const int days = IniParser::getInstance().getInt("general.NUMBER_OF_DAYS");
	const int hoursPerDay = IniParser::getInstance().getInt(
			"general.NUMBER_OF_HOURS_PER_DAY");
	const int morningStartTime = IniParser::getInstance().getInt(
			"general.MORNING_START_TIME");

	//add FINISHEDSIMULATION event at the end of specified days
	boost::posix_time::time_duration td = boost::posix_time::hours(days * 24);
	getEvents()->addEvent(td, EventContent
	{ this, EventType::FINISHEDSIMULATION });

	//turn on the machines at morningStartTime every day
	boost::posix_time::time_duration morning = boost::posix_time::hours(
			morningStartTime);
	for (int i = 0; i < days; ++i)
	{
		getEvents()->addEvent((morning + boost::posix_time::hours(i * 24)),
				EventContent
				{ this, EventType::TURNON });
	}
	//turn Off the machines at stopTime every day
	boost::posix_time::time_duration stopTime = boost::posix_time::hours(
			morningStartTime + hoursPerDay);
	for (int i = 0; i < days; ++i)
	{
		getEvents()->addEvent((stopTime + boost::posix_time::hours(i * 24)),
				EventContent
				{ this, EventType::TURNOFF });
	}
	generatedWorkTimeMinutes = generateWorkTimeMinutes();

	setCurrentState(std::shared_ptr<AbstractState>(new OffState(this)));
	this->currentState->entry();
}

void Machine::setCurrentState(
		const std::shared_ptr<AbstractState>& currentState)
{
	DEBUG_MSG("Machine " << std::to_string(getConfig().id) << " " << __PRETTY_FUNCTION__ << " currentState: " << typeid(*currentState).name());
	this->currentState = currentState;
}
void Machine::runMachineThread()
{
	while (clock->isSimulationRunning())
	{
		runMachine();
	}
	DEBUG_MSG("machine tread " + std::to_string(getMachineId()) + " stopped.");
	exit(EXIT_FAILURE); //TODO: dit oplossen
}

void Machine::runMachine()
{
	//loop runs if simulation is running
	std::pair<boost::posix_time::time_duration, EventContent> event = events->getFirstEvent();
	if (clock->isPaused() == false && event.second.eventType == EventType::FINISHEDSIMULATION)
	{
		//simulation will be stopped if FINISHEDSIMULATION occurs
		DEBUG_MSG("machine " + std::to_string(getMachineId()) + " handles " + events->printEvent(event.first, event.second) + " ");
		events->removeFirstEvent();
		clock->setSimulationTime(event.first);
		clock->stopSimulation();
	}
	else
	{
		if (clock->isPaused() == false && event.second.machine == this)
		{
			//clock is not paused and event is adressed to this machine
			DEBUG_MSG("machine " + std::to_string(getMachineId()) + " handles " + events->printEvent(event.first, event.second) + " ");
			clock->setSimulationTime(event.first);

			//handles events
			const bool eventHandled = currentState->handleEvent(event.second);
			DEBUG_MSG("eventHandled: " << eventHandled);
			if (!eventHandled)
			{
				events->removeFirstEvent();
				return;
			}

			/*	86400 is the total number of seconds in a day.
			 This is a hack, because boost::posix_time::time_duration has no function 'total_hours',
			 which forced me to calculate with seconds.
			 The +1 is to let the day count start at 1
			 */
			pc->log(
					std::to_string(((event.first.total_seconds() / 86400) + 1))
							+ "," + std::to_string((event.first.hours() % 24))
							+ ":" + std::to_string(event.first.minutes())
							+ ",M," + std::to_string(config.id) + ","
							+ config.MachineName + ","
							+ events->printEventType(event.second.eventType)
							+ "," + std::to_string(currentAmountOfWork) + ","
							+ std::to_string(
									(event.first.total_milliseconds())));

			events->removeFirstEvent();
		}
	}
}

void Machine::turnOn()
{
	events->addEvent(clock->getSimulationTime(), EventContent
	{ this, EventType::TURNON });
}

void Machine::turnOff()
{
	currentAmountOfWork = 0;
	events->addEvent(clock->getSimulationTime(), EventContent
	{ this, EventType::TURNOFF });
}

unsigned int Machine::generateWorkTimeMinutes()
{
	static std::mt19937 gen(seed);
	std::uniform_real_distribution<> distribution(0, (getConfig().MTBF * 60 * 2));
	if (getConfig().MTBF == 0) return 10000000000;
	return distribution(gen);
}
