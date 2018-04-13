/*
 * machineNetworkHandler.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */

#include "machineNetworkHandler.hpp"
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "controlNetworkHandler.hpp"
#include "Client.hpp"
#include "CommunicationService.hpp"
#include "../Logger/Queued_logger.hpp"
#include "../IniParser/IniParser.hpp"
#include "../Defines.hpp"

using Messaging::Message;

machineNetworkHandler::machineNetworkHandler(ProductionControl* ppcPtr) :
		communicating(false), ppcPtr(ppcPtr), localPort(
				IniParser::getInstance().getString("general.LOCAL_PORT")), remoteIP(
				IniParser::getInstance().getString(
						"general.PRODUCTION_CONTROL_IP")), remotePort(
				IniParser::getInstance().getString(
						"general.PRODUCTION_CONTROL_PORT"))
{
}

machineNetworkHandler::~machineNetworkHandler()
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	stopCommunicating();
}

void machineNetworkHandler::startCommunicating()
{
	communicating = true;
	Messaging::CommunicationService::getCommunicationService().runRequestHandler(
			toPtr<machineNetworkHandler>(), std::stoi(localPort));
}

void machineNetworkHandler::stopCommunicating()
{
	if (communicating)
	{
		communicating = false;
		Messaging::CommunicationService::getCommunicationService().stop();
	}
}

void machineNetworkHandler::handleRequest(Message& aMessage)
{
	DEBUG_MSG(__PRETTY_FUNCTION__);
	switch (aMessage.getMessageType())
	{
	case controlNetworkHandler::OKMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int time = std::stoi(rit->str());
		time_duration td = seconds(time);
		++rit;
		int machineId = std::stoi(rit->str());
		++rit;
		int stateId = std::stoi(rit->str());
		MachineState state = static_cast<MachineState>(stateId);
		ppcPtr->OK(td, machineId, state);
		break;
	}
	case controlNetworkHandler::NOKMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int time = std::stoi(rit->str());
		time_duration td = seconds(time);
		++rit;
		int machineId = std::stoi(rit->str());
		ppcPtr->NOK(td, machineId);
		break;
	}
	case controlNetworkHandler::LOGMESSAGE:
	{
		ppcPtr->log(aMessage.getBody());
		break;
	}
	case controlNetworkHandler::FINISHEDMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int nrOfOutput = std::stoi(rit->str());
		++rit;
		int time = std::stoi(rit->str());
		time_duration td = seconds(time);
		++rit;
		int machineId = std::stoi(rit->str());
		ppcPtr->finished(nrOfOutput, td, machineId);
		break;
	}
	case controlNetworkHandler::SIMULATIONSTOPPEDMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int time = std::stoi(rit->str());
		time_duration td = seconds(time);
		ppcPtr->simulationStopped(td);
		break;
	}
	case controlNetworkHandler::MACHINEBROKENMESSAGE:
	{
		std::string input = aMessage.getBody();
		static std::regex regex("\\d+");
		std::regex_iterator<std::string::iterator> rit(input.begin(),
				input.end(), regex);
		std::regex_iterator<std::string::iterator> rend;
		int time = std::stoi(rit->str());
		time_duration td = seconds(time);
		++rit;
		int machineId = std::stoi(rit->str());
		ppcPtr->NOK(td, machineId);
		break;
	}
	default:
		Queued_logger::get_instance().log(
				"Unknown message type: " + aMessage.getMessageType());
		break;
	}
}

void machineNetworkHandler::handleResponse(const Message& aMessage)
{
	switch (aMessage.getMessageType())
	{
	default:
		Queued_logger::get_instance().log(aMessage.getBody());
		break;
	}
}

void machineNetworkHandler::sendMessage(Messaging::Message& aMessage)
{
	Messaging::Client client(remoteIP, remotePort,
			toPtr<controlNetworkHandler>());
	client.dispatchMessage(aMessage);
	std::this_thread::sleep_for (std::chrono::milliseconds(10));
}

void machineNetworkHandler::createMachine(MachineConfig config)
{
	std::string configmessage = config.toString();
	Messaging::Message message(machineNetworkHandler::CREATEMACHINEMESSAGE,
			configmessage);
	sendMessage(message);
}

void machineNetworkHandler::setConfig(MachineConfig config, int machineId)
{
	std::ostringstream data;
	Messaging::Message message(machineNetworkHandler::SETCONFIGMESSAGE,
			data.str());
	sendMessage(message);
}

void machineNetworkHandler::turnOn(int machineId)
{
	std::ostringstream data;
	data << machineId;
	Messaging::Message message(machineNetworkHandler::TURNONMESSAGE,
			data.str());
	sendMessage(message);
}

void machineNetworkHandler::turnOff(int machineId)
{
	std::ostringstream data;
	data << machineId;
	Messaging::Message message(machineNetworkHandler::TURNOFFMESSAGE,
			data.str());
	sendMessage(message);
}

void machineNetworkHandler::getStatus(int machineId)
{
	std::ostringstream data;
	data << machineId;
	Messaging::Message message(machineNetworkHandler::GETSTATUSMESSAGE,
			data.str());
	sendMessage(message);
}

void machineNetworkHandler::startWorking(int nrOfProducts, int machineId)
{
	std::ostringstream data;
	data << nrOfProducts << " " << machineId;
	Messaging::Message message(machineNetworkHandler::STARTWORKINGMESSAGE,
			data.str());
	sendMessage(message);
}

void machineNetworkHandler::startClock()
{
	std::string data = "startclock";
	Messaging::Message message(machineNetworkHandler::STARTCLOCKMESSAGE, data);
	sendMessage(message);
}

void machineNetworkHandler::pauseClock()
{
	std::string data = "pauseclock";
	Messaging::Message message(machineNetworkHandler::PAUSECLOCKMESSAGE, data);
	sendMessage(message);
}

void machineNetworkHandler::resumeClock()
{
	std::string data = "resumeclock";
	Messaging::Message message(machineNetworkHandler::RESUMECLOCKMESSAGE, data);
	sendMessage(message);
}

void machineNetworkHandler::stopClock()
{
	std::string data = "stopclock";
	Messaging::Message message(machineNetworkHandler::STOPCLOCKMESSAGE, data);
	sendMessage(message);
}
