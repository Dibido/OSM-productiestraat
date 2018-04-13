/*
 * machineNetworkHandler.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */
#ifndef EXE1_machineNetworkHandler_H_
#define EXE1_machineNetworkHandler_H_

#include <memory>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "machineNetworkHandlerMethods.hpp"
#include "Message.hpp"
#include "MessageHandler.hpp"
#include "../../Exe2/MachineConfig.hpp"
#include "../ProductionControl.hpp"

class ProductionControl;

using boost::posix_time::time_duration;
using boost::property_tree::ptree;
using Messaging::Message;

class machineNetworkHandler;
typedef std::shared_ptr<machineNetworkHandler> MachineNetworkHandlerPtr;

/**
 * @brief machineNetworkHandler class used for communication with the ProxyControl class.
 */
class machineNetworkHandler: public Messaging::MessageHandler,
		public machineNetworkHandlerMethods,
		public std::enable_shared_from_this<machineNetworkHandler>
{
public:
	explicit machineNetworkHandler(ProductionControl* ppcPtr = nullptr);
	virtual ~machineNetworkHandler();
	/**
	 * This function is called by a ServerSesssion whenever a message is received. If the request is handled,
	 * any response *must* be set in the Message argument. The message argument is then echoed back to the
	 * requester, probably a ClientSession.
	 *
	 * @see Messaging::RequestHandler::handleRequest( Messaging::Message& aMessage)
	 */
	virtual void handleRequest(Message& aMessage);
	/**
	 * This function is called by a ClientSession whenever a response to a previous request is received.
	 *
	 * @see Messaging::ResponseHandler::handleResponse( const Messaging::Message& aMessage)
	 */
	virtual void handleResponse(const Message& aMessage);
	/**
	 * Starts a ServerConnection that listens at port 12345 unless given
	 * an other port by specifying a command line argument -local_port=port
	 */
	void startCommunicating();
	/**
	 * Connects to the ServerConnection that listens at port 12345 unless given
	 * an other port by specifying a command line argument -local_port=port
	 * and sends a message with messageType "1" and a body with "stop"
	 *
	 */
	void stopCommunicating();
	/**
	 * @brief Sends a message to the remote client
	 * @param The message to be sent
	 * @return void
	 * @pre No message is sent
	 * @post the message is sent to the remote client
	 */
	void sendMessage(Messaging::Message& aMessage);
	/**
	 * Enum for the diffent messageTypes a message can have.
	 */
	enum MachineMessageTypes
	{
		CREATEMACHINEMESSAGE,
		SETCONFIGMESSAGE,
		TURNONMESSAGE,
		TURNOFFMESSAGE,
		GETSTATUSMESSAGE,
		STARTWORKINGMESSAGE,
		STARTCLOCKMESSAGE,
		PAUSECLOCKMESSAGE,
		RESUMECLOCKMESSAGE,
		STOPCLOCKMESSAGE
	};
	/**
	 * Send a createMachine message
	 * @param configuration for the new machine
	 * @pre Machine is not created
	 * @post Machine is created with configuration
	 * @return void
	 */
	virtual void createMachine(MachineConfig config);
	/**
	 *Sets the configuration of a machine to a new configuration
	 *@param the new configuration for the machine
	 *@pre
	 *@post
	 *@return void
	 */
	virtual void setConfig(MachineConfig config, int machineId);
	/**
	 *Turns on a machine
	 *@param machineId
	 *@pre machine is Off
	 *@post machine is On
	 *@return void
	 */
	virtual void turnOn(int machineId);
	/**
	 *Turns off a machine
	 *@param machineIdProductionControl*
	 *@pre machine is On
	 *@post machine is Off
	 */
	virtual void turnOff(int machineId);
	/**
	 *Gets the status of a machine
	 *@param machineId
	 *@pre machine Status is unknown
	 *@post machine Status is known
	 *@return void
	 */
	virtual void getStatus(int machineId);
	/**
	 *Sets a machine to work
	 *@param nrOfProducts number of products to be processed
	 *@param machineId
	 */
	virtual void startWorking(int nrOfProducts, int machineId);
	/**
	 *@brief Starts the machine control clock
	 *@param none
	 */
	virtual void startClock();
	/**
	 *@brief pauses the machine control clock
	 *@param none
	 */
	virtual void pauseClock();
	/**
	 *@brief resumes the machine control clock
	 *@param none
	 */
	virtual void resumeClock();
	/**
	 *@brief stops the machine control clock
	 *@param none
	 */
	virtual void stopClock();
	/*
	 * @briefConverts the contained ModelObject to a std::shared_ptr<DestinationType>
	 * @param none
	 * @return shared pointer to the object
	 * @return std::shared_ptr<DestinationType>
	 */
	template<typename DestinationType>
	std::shared_ptr<DestinationType> toPtr()
	{
		return std::dynamic_pointer_cast<DestinationType>(shared_from_this());
	}
	/**
	 * Whether the handler is communicating
	 */
	bool communicating;
	inline bool isCommunicating()
	{
		return communicating;
	}

	void setPcPtr(ProductionControl* ppcPtr)
	{
		this->ppcPtr = ppcPtr;
	}

	//Pointer to the production control for handling network responses
	ProductionControl* ppcPtr;
	//network variables
	std::string localPort = "12344";
	std::string remoteIP = "localhost";
	std::string remotePort = "12345";
};

#endif /* EXE1_machineNetworkHandler_H_ */
