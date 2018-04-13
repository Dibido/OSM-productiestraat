/*
 * controlNetworkHandler.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */

#include "controlNetworkHandler.hpp"

#include <boost/date_time/time_duration.hpp>
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>

#include "Client.hpp"
#include "CommunicationService.hpp"
#include "machineNetworkHandler.hpp"
#include "../Defines.hpp"
#include "../Logger/Queued_logger.hpp"
#include "../IniParser/IniParser.hpp"

typedef std::shared_ptr<machineNetworkHandler> MachineNetworkHandlerPtr;

controlNetworkHandler::controlNetworkHandler(ProxyProductionControl* ppcPtr) :
		communicating(false), proxyProductionControlPtr(ppcPtr), localPort(
				IniParser::getInstance().getString("general.LOCAL_PORT")), remoteIP(
				IniParser::getInstance().getString(
						"general.MACHINE_CONTROL_IP")), remotePort(
				IniParser::getInstance().getString(
						"general.MACHINE_CONTROL_PORT"))
{
}

controlNetworkHandler::~controlNetworkHandler()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	stopCommunicating();
}

void controlNetworkHandler::startCommunicating()
{
	communicating = true;
	Messaging::CommunicationService::getCommunicationService().runRequestHandler(
			toPtr<controlNetworkHandler>(), std::stoi(localPort));
}

void controlNetworkHandler::stopCommunicating()
{
	if (communicating)
	{
		communicating = false;
		Messaging::CommunicationService::getCommunicationService().stop();
	}
}

void controlNetworkHandler::handleRequest(Message& aMessage)
{
	switch (aMessage.getMessageType())
	{
	case machineNetworkHandler::CREATEMACHINEMESSAGE:
	{
		std::string config = aMessage.getBody();
		MachineConfig mc;
		mc.fromString(config);
		proxyProductionControlPtr->makeMachine(mc);
		break;
	}
	case machineNetworkHandler::SETCONFIGMESSAGE:
	{
		//TODO: call setConfig method
		break;
	}
	case machineNetworkHandler::TURNONMESSAGE:
	{
		int machineId = std::stoi(aMessage.getBody());
		proxyProductionControlPtr->getMachine(machineId)->turnOn();
		break;
	}
	case machineNetworkHandler::TURNOFFMESSAGE:
	{
		int machineId = std::stoi(aMessage.getBody());
		proxyProductionControlPtr->getMachine(machineId)->turnOff();
		break;
	}
	case machineNetworkHandler::GETSTATUSMESSAGE:
	{
		//TODO call getStatus method
		break;
	}
	case machineNetworkHandler::STARTWORKINGMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int nrOfProducts = std::stoi(rit->str());
		++rit;
		int machineId = std::stoi(rit->str());
		proxyProductionControlPtr->getMachine(machineId)->startWork(
				nrOfProducts);
		break;
	}
	case machineNetworkHandler::STARTCLOCKMESSAGE:
	{
		proxyProductionControlPtr->getClock().startSimulation();
		break;
	}
	case machineNetworkHandler::PAUSECLOCKMESSAGE:
	{
		proxyProductionControlPtr->getClock().pause();
		break;
	}
	case machineNetworkHandler::RESUMECLOCKMESSAGE:
	{
		proxyProductionControlPtr->getClock().resume();
		break;
	}
	case machineNetworkHandler::STOPCLOCKMESSAGE:
	{
		proxyProductionControlPtr->getClock().stopSimulation();
		break;
	}
	default:
		break;
	}
}

void controlNetworkHandler::handleResponse(const Message& aMessage)
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	switch (aMessage.getMessageType())
	{
	case controlNetworkHandler::LOGMESSAGE:
	{
		break;
	}
	default:
		break;
	}
}

void controlNetworkHandler::sendMessage(Messaging::Message& aMessage)
{
	Messaging::Client client(remoteIP, remotePort,
			toPtr<machineNetworkHandler>());
	DEBUG_MSG(aMessage.message);
	client.dispatchMessage(aMessage);
	std::this_thread::sleep_for (std::chrono::milliseconds(10));
}

void controlNetworkHandler::OK(time_duration time, int machineId,
		MachineState currentState)
{
	std::ostringstream data;
	data << time.total_seconds() << " " << machineId << " "
			<< static_cast<int>(currentState);
	Messaging::Message message(controlNetworkHandler::OKMESSAGE, data.str());
	sendMessage(message);
}

void controlNetworkHandler::NOK(time_duration time, int machineId)
{
	std::ostringstream data;
	data << time.total_seconds() << " " << machineId;
	Messaging::Message message(controlNetworkHandler::NOKMESSAGE, data.str());
	sendMessage(message);
}

void controlNetworkHandler::log(const std::string& text)
{
	std::ostringstream data;
	data << text;
	Messaging::Message message(controlNetworkHandler::LOGMESSAGE, data.str());
	sendMessage(message);
}

void controlNetworkHandler::finished(int nrOfOutput, time_duration time,
		int machineId)
{
	std::ostringstream data;
	data << nrOfOutput << " " << time.total_seconds() << " " << machineId;
	Messaging::Message message(controlNetworkHandler::FINISHEDMESSAGE,
			data.str());
	sendMessage(message);
}

void controlNetworkHandler::simulationStopped(time_duration time)
{
	std::ostringstream data;
	data << time.total_seconds();
	Messaging::Message message(controlNetworkHandler::SIMULATIONSTOPPEDMESSAGE,
			data.str());
	sendMessage(message);
}

void controlNetworkHandler::machineBroken(time_duration time, int machineId)
{
	std::ostringstream data;
	data << time.total_seconds() << " " << machineId;
	Messaging::Message message(controlNetworkHandler::MACHINEBROKENMESSAGE,
			data.str());
	sendMessage(message);
}
