/*
 * ProductionControl.cpp
 *
 *  Created on: 16 nov. 2017
 *      Author: Stefan
 */
#include <chrono>
#include <thread>
#include "ProductionControl.hpp"


// cppcheck-suppress passedByValue
ProductionControl::ProductionControl(MachineNetworkHandlerPtr mnhPtr) :
		ppc(new ProxyProductionControl(this, nullptr)), mnhPtr(
				mnhPtr), pClock(new ProxyClock(&ppc->getClock(), mnhPtr))
{
}

ProductionControl::~ProductionControl()
{

}

unsigned long ProductionControl::produce_batch(unsigned long batch_size)
{
	DEBUG_MSG(__PRETTY_FUNCTION__ << "batch_size: " << batch_size);
	std::map<unsigned long, unsigned long> firstBufferSizes = calculateFirstBufferSize();

	for (auto& iter : firstBufferSizes)
	{
 		buffers.find(iter.first)->second.setNumberOfProducts(iter.second * batch_size);
		DEBUG_MSG("calculateFirstBufferSize() * batch_size: " << iter.second * batch_size);

		/*	86400 is the total number of seconds in a day.
		 This is a hack, because boost::posix_time::time_duration has no function 'total_hours',
		 which forced me to calculate with seconds.
		 The +1 is to let the day count start at 1
		 */
		log(
				std::to_string(
						((FactoryClock::getInstance()->getSimulationTime().total_seconds() / 86400) + 1))
						+ ","
						+ std::to_string((FactoryClock::getInstance()->getSimulationTime().hours() % 24))
						+ ":" + std::to_string(FactoryClock::getInstance()->getSimulationTime().minutes())
						+ ",B,"
						+ std::to_string(iter.first)
						+ ",SET," + std::to_string(iter.second * batch_size) + ","
						+ std::to_string(iter.second * batch_size)
						+ ","
						+ std::to_string(
								(FactoryClock::getInstance()->getSimulationTime().total_milliseconds())));
	}
	checkMachines();
	pClock->resume();

	while (!batchFinished())
	{
		if (!FactoryClock::getInstance()->isRunning()) break;
	}

	pClock->pause();
	std::this_thread::sleep_for(std::chrono::milliseconds(10));


	DEBUG_MSG("batch Finished");
	return 0;
}

std::map<unsigned long, unsigned long> ProductionControl::calculateFirstBufferSize()
{
	std::map<unsigned long, unsigned long> partsNeeded;
	std::map<unsigned long,unsigned long> FirstBuffers = getFirstBuffers();

	for (auto& iter : FirstBuffers)
	{
		unsigned long MachineOrder = iter.first;
		std::stack<unsigned long> partsNeededForAllMachines;

		bool calculation = true;
		while (calculation)
		{
			unsigned long partsNeeded = localMachines.find(getMachineChild(MachineOrder).front())->second.getConfig().partsNeeded.at(getMachineChild(MachineOrder).at(1));
			partsNeededForAllMachines.push(partsNeeded);
			MachineOrder = localMachines.find(getMachineChild(MachineOrder).front())->second.getConfig().nextId.front();

			if (doesBufferHaveParent(MachineOrder) == false)
			{
				calculation = false;
			}
		}
		partsNeeded.insert(std::pair<unsigned long, unsigned long>(iter.first,getPartsNeededForOnePart(partsNeededForAllMachines)));
	}
	return partsNeeded;
}

unsigned long ProductionControl::getPartsNeededForOnePart(std::stack<unsigned long> partsNeededForAllMachines)
{
	unsigned long totaal = 0;
	while (!partsNeededForAllMachines.empty())
	  {
		if(totaal == 0){
			totaal = partsNeededForAllMachines.top();
		}else{
			totaal = totaal * partsNeededForAllMachines.top();
		}
	    partsNeededForAllMachines.pop();
	  }
	return totaal;
}

std::vector<unsigned long> ProductionControl::getMachineChild(unsigned long bufferId)
{
	signed long machineId = -1;
	unsigned long place;

	for (auto& iter : boost::adaptors::reverse(localMachines))
	{
		for (unsigned long idx = 0;
				idx < iter.second.getConfig().parentId.size(); ++idx)
		{
			if (iter.second.getConfig().parentId.at(idx) == bufferId)
			{
				machineId = iter.first;
				place = idx;
			}
		}
	}
	if (machineId == -1)
	{
		throw std::invalid_argument("No machine found for buffer: " + std::to_string(bufferId));
	}

	std::vector<unsigned long> vector;
	vector.push_back(machineId);
	vector.push_back(place);
	return vector;
}

bool ProductionControl::doesBufferHaveParent(unsigned long bufferId)
{
	signed long machineId = -1;

	for (auto& iter : boost::adaptors::reverse(localMachines))
	{
		for (unsigned long idx = 0;
				idx < iter.second.getConfig().parentId.size(); ++idx)
		{
			if (iter.second.getConfig().parentId.at(idx) == bufferId)
			{
				machineId = iter.first;
				return true;
			}
		}
	}
	if (machineId == -1)
	{
		return false;
	}

	return true;
}


std::map<unsigned long,unsigned long> ProductionControl::getFirstBuffers()
{
	std::map<unsigned long,unsigned long> b;

	for (auto& iter : boost::adaptors::reverse(localMachines))
	{
		if (iter.second.isActive()){
			for (unsigned long idx = 0; idx < iter.second.getConfig().parentId.size(); ++idx)
			{
				unsigned long count = 0;
				unsigned int valueParent = iter.second.getConfig().parentId.at(idx);

				for (auto& itr : boost::adaptors::reverse(localMachines))
				{
					unsigned int valueChild = itr.second.getConfig().nextId.at(0);
					if (valueParent == valueChild)
					{
					DEBUG_MSG("NOTFOUND: " << valueParent);
					DEBUG_MSG("NOTFOUND: " << valueChild);
					++count;
					}
				}
				if (count == 0)
				{
					Buffer m = buffers.find(iter.second.getConfig().parentId.at(idx))->second;
					unsigned long value = m.getId();
					b.insert(std::pair<unsigned long,unsigned long>(value,idx));
					DEBUG_MSG("value: " << value);
				}
			}
		}
	}
	return b;
}

void ProductionControl::init(const std::string& configFile)
{
	mnhPtr->setPcPtr(this);
#if NETWORK > 0
	//Set networkHandler to start communicating.
	mnhPtr->startCommunicating();
#endif

//	pClock->stopSimulation(); // TODO: deze werkt niet

	LoadConfiguration().makeMachines(this, mnhPtr,
			configFile, machines,
			localMachines, buffers, ppc);

	DEBUG_MSG("Waiting for response from machines...");

	machinesReady();

	return;
}

void ProductionControl::init()
{
	mnhPtr->setPcPtr(this);
#if NETWORK > 0
	//Set networkHandler to start communicating.
	mnhPtr->startCommunicating();
#endif

	pClock->startSimulation();
	pClock->pause();

	return;
}

void ProductionControl::start()
{

	getchar();
	pClock->resume();

	return;
}

void ProductionControl::finished(int nrOfOutput,
		boost::posix_time::time_duration time, int machineId)
{
	DEBUG_MSG(__PRETTY_FUNCTION__ << " machineId: " << machineId);
	FactoryClock::getInstance()->setSimulationTime(time);
	buffers.at(localMachines.at(machineId).getConfig().nextId.front()) +=
			nrOfOutput;

	/*	86400 is the total number of seconds in a day.
	 This is a hack, because boost::posix_time::time_duration has no function 'total_hours',
	 which forced me to calculate with seconds.
	 The +1 is to let the day count start at 1
	 */
	log(
			std::to_string(
					((FactoryClock::getInstance()->getSimulationTime().total_seconds() / 86400) + 1))
					+ ","
					+ std::to_string((FactoryClock::getInstance()->getSimulationTime().hours() % 24))
					+ ":" + std::to_string(FactoryClock::getInstance()->getSimulationTime().minutes())
					+ ",B,"
					+ std::to_string(
							localMachines.at(machineId).getConfig().nextId.front())
					+ ",ADD," + std::to_string(nrOfOutput) + ","
					+ std::to_string(
							buffers.at(
									localMachines.at(machineId).getConfig().nextId.front()).getNumberOfProducts())
					+ ","
					+ std::to_string(
							(FactoryClock::getInstance()->getSimulationTime().total_milliseconds())));

	localMachines.find(machineId)->second.setState(MachineState::ON);

	if (!batchFinished())
	{
		checkMachines();
		pClock->resume();
	}
}

void ProductionControl::OK(boost::posix_time::time_duration time, int machineId,
		MachineState currentState)
{
	DEBUG_MSG(
			__PRETTY_FUNCTION__ << " machineId: " << machineId << " currentState: " << std::to_string(static_cast<int>(currentState)));
	FactoryClock::getInstance()->setSimulationTime(time);

	if (localMachines.find(machineId)->second.isReady() == false)
	{
		localMachines.find(machineId)->second.setReady(true);
		return;
	}

	MachineState localMachineState =
			localMachines.find(machineId)->second.getState();

	if (!batchFinished())
	{
		if (localMachineState != MachineState::BUSY)
		{

			DEBUG_MSG(
					"OK: machineId: " << machineId << " localMachineState " << std::to_string(static_cast<int>(localMachines.find(machineId)->second.getState())));
			localMachines.find(machineId)->second.setState(currentState);

			DEBUG_MSG(
					"OK: machineId: " << machineId << " localMachineState " << std::to_string(static_cast<int>(localMachines.find(machineId)->second.getState())));
			checkMachines();
		}
		pClock->resume();
	}
}

void ProductionControl::NOK(boost::posix_time::time_duration time,
		int machineId)
{
	DEBUG_MSG(__PRETTY_FUNCTION__ << " machineId: " << machineId);
	FactoryClock::getInstance()->setSimulationTime(time);

	localMachines.find(machineId)->second.setState(MachineState::BROKEN);

	if (!batchFinished())
	{
		checkMachines();
		pClock->resume();
	}
}

void ProductionControl::checkMachines()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	for (auto& iter : boost::adaptors::reverse(localMachines))
	{
		if (iter.second.getState() == MachineState::ON && iter.second.isActive()) // machinestatus == OK
		{

			DEBUG_MSG("Machine state is ON");
			const int childBufferId = iter.second.getConfig().nextId.front();

			std::map<int, Buffer> classParentBuffer;

			for (size_t i = 0; i < iter.second.getConfig().parentId.size(); ++i)
			{
				DEBUG_MSG("iter.second.getConfig().parentId.at(i): " << iter.second.getConfig().parentId.at(i));
				Buffer b =
						buffers.find(iter.second.getConfig().parentId.at(i))->second;

				classParentBuffer.insert(
						std::pair<int, Buffer>(
								iter.second.getConfig().parentId.at(i), b));
			}

			DEBUG_MSG("childBufferId: " << childBufferId);
			DEBUG_MSG("parentId: " << classParentBuffer.begin()->second.getId());
			DEBUG_MSG("parentId: " << classParentBuffer.begin()->first);
			DEBUG_MSG("parentId: " << iter.second.getConfig().parentId.front());

			std::map<int, std::pair<int, int>> inputValue =
					iter.second.getMachineInput(
							buffers.find(childBufferId)->second,
							classParentBuffer);

			std::vector<int> value;


			for (auto& idx : inputValue)
			{
				const int timeNeededByMachine = iter.second.calculateProcessTime(idx.second.first, iter.second.getConfig()) / 60 / 1000;
				const int closingTimeMinutes = ((IniParser::getInstance().getInt("general.MORNING_START_TIME") + IniParser::getInstance().getInt("general.NUMBER_OF_HOURS_PER_DAY")) * 60);
				const int timeThisDayMinutes = (FactoryClock::getInstance()->getSimulationTime().total_seconds() / 60) % (24 * 60);

				DEBUG_MSG("\033[1;34mtimeThisDayMinutes: " + std::to_string(timeThisDayMinutes) + " timeNeededByMachine: " + std::to_string(timeNeededByMachine) + " timeLeftToday: " + std::to_string((closingTimeMinutes - timeThisDayMinutes)) + "   \033[0m");

				if ((closingTimeMinutes - timeThisDayMinutes) > timeNeededByMachine + 1)
				{
					if (idx.second.first > 0)
					{
						value.push_back(idx.second.first);
						iter.second.setState(MachineState::BUSY);
						buffers.find(idx.first)->second -= idx.second.first;

						/*	86400 is the total number of seconds in a day.
						 This is a hack, because boost::posix_time::time_duration has no function 'total_hours',
						 which forced me to calculate with seconds.
						 The +1 is to let the day count start at 1
						 */
						log(std::to_string(((FactoryClock::getInstance()->getSimulationTime().total_seconds()/ 86400) + 1)) + ","
									+ std::to_string((FactoryClock::getInstance()->getSimulationTime().hours()% 24)) + ":"
									+ std::to_string(FactoryClock::getInstance()->getSimulationTime().minutes())
									+ ",B," + std::to_string(idx.first)
									+ ",SUBSTRACT,"
									+ std::to_string(idx.second.first) + ","
									+ std::to_string(buffers.find(idx.first)->second.getNumberOfProducts())
									+ ","
									+ std::to_string((FactoryClock::getInstance()->getSimulationTime().total_milliseconds())));
					}
				}
			}
			if (value.size() > 0)
			{
				iter.second.setCurrentAmountOfWork(value.at(0));
				machines.find(iter.first)->second.startWork(value.at(0));
			}
		}
	}
}


/*static*/void ProductionControl::log(std::string log_data)
{
	Queued_logger::get_instance().log(log_data);
}

void ProductionControl::updateProductionLineConfig(const ProductionLineConfig& productionLineConfig)
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	pClock->pause();
	buffers.clear();

	for (auto& iter : productionLineConfig.bcm)
	{

		Buffer buffer(iter.second.numberOfProducts, iter.second.maxBuffer, iter.second.id);
		DEBUG_MSG("Buffer created id: " << buffer.getId() << " numberOfProducts: " << buffer.getNumberOfProducts() << " maxBuffer: " << buffer.getMaxBuffer());
		buffers.insert(std::pair<int, Buffer>(buffer.getId(), buffer));
	}

	for (auto& iter : localMachines)
	{

		iter.second.setActive(false);
	}

	for (auto& iter : productionLineConfig.mcm)
	{

		if (machines.count(iter.first))
		{

			localMachines.find(iter.first)->second.setReady(false);
			localMachines.find(iter.first)->second.setActive(true);
			localMachines.find(iter.first)->second.setState(MachineState::INIT);
			machines.find(iter.first)->second.setConfig(iter.second);
			localMachines.find(iter.first)->second.setConfig(iter.second);
			DEBUG_MSG("Machine updated id: " << iter.second.id);
		}
		else
		{

			localMachines.insert(std::pair<int, LocalMachine>(iter.second.id, (LocalMachine(iter.second))));
			machines.insert(std::pair<int, ProxyMachine>(iter.second.id, ProxyMachine(iter.second, mnhPtr, ppc)));
			DEBUG_MSG("Machine created id: " << iter.second.id);

		}
	}

	machinesReady();

	return;
}

void ProductionControl::simulationStopped(boost::posix_time::time_duration time)
{
	FactoryClock::getInstance()->setSimulationTime(time);
	Queued_logger::get_instance().stop();
	Queued_logger::get_instance().switch_logger_type(new Log_to_file("test.csv"));
	Queued_logger::get_instance().log("");
	Queued_logger::get_instance().log("MACHINE,STATISTICS,VALUE");

	std::cout << std::endl << "Simulation finished." << std::endl;
	std::cout << "\033[1;97mStatistics:\033[0m" << std::endl;
	FactoryClock::getInstance()->setRunning(false);
	for (auto& iter : localMachines)
	{
		iter.second.printStats();
	}
}

bool ProductionControl::batchFinished()
{
	for (auto& iter : localMachines)
	{
		if (iter.second.isActive()){
		if (iter.second.getState() == MachineState::BUSY)
		{
			return false;
		}
		bool machineHasEnoughInput = true;
		unsigned long iteratorIndex = 0;
		for (auto& iter1 : iter.second.getConfig().parentId)
		{
			// amount in buffer < partsneeded
			if (buffers.find(iter1)->second.getNumberOfProducts() < iter.second.getConfig().partsNeeded.at(iteratorIndex))
			{
				machineHasEnoughInput = false;
			}
			++iteratorIndex;
		}
		if (machineHasEnoughInput) return false;
		}
	}
	return true;
}


void ProductionControl::machinesReady()
{
	DEBUG_MSG("Waiting for response from machines... ");
	for (;;)
	{
		bool allMachinesReady = true;
		for (auto& iter : localMachines)
		{
			if (iter.second.isReady() == false)
			{
				allMachinesReady = false;
			}
		}
		if (allMachinesReady == true)
		{
			DEBUG_MSG("All machines are ready.");
			break;
		}
	}
}
