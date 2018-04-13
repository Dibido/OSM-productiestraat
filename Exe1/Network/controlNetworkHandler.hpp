/*
 * controlNetworkHandler.hpp
 *
 *  Created on: Nov 20, 2017
 *      Author: dibran
 */

#ifndef EXE1_PROXYCONTROL_H_
#define EXE1_PROXYCONTROL_H_

#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <boost/property_tree/ptree_fwd.hpp>
#include <memory>
#include <string>

#include "../../Exe2/MachineState.hpp"
#include "../../Exe2/ProxyProductionControl.hpp"
#include "controlNetworkHandlerMethods.hpp"
#include "Message.hpp"
#include "MessageHandler.hpp"

class ProxyProductionControl;

using boost::property_tree::ptree;
using Messaging::Message;
using namespace boost::posix_time;

class controlNetworkHandler;
typedef std::shared_ptr<controlNetworkHandler> ControlNetworkHandlerPtr;

/**
 * @brief ProxyControl class used for communication with the ProxyMachine class.
 */
class controlNetworkHandler: public Messaging::MessageHandler,
		public controlNetworkHandlerMethods,
		public std::enable_shared_from_this<controlNetworkHandler>
{
public:
	explicit controlNetworkHandler(ProxyProductionControl* ppcPtr = nullptr);
	virtual ~controlNetworkHandler();
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
	 * Send an OK message to the proxyControl proxy
	 * @param machineId
	 * @pre Message is not sent.
	 * @post Message is sent.
	 * @return void
	 */
	virtual void OK(time_duration time, int machineId,
			MachineState currentState);
	/**
	 * Send an NOK message to the proxyControl proxy
	 * @param machineId
	 * @pre Message is not sent.
	 * @post Message is sent.
	 * @return void
	 */
	virtual void NOK(time_duration time, int machineId);
	/**
	 * Log information to the logger
	 * @param text that should be logged, time of the event, machineId of the machine
	 * @pre event is not logged
	 * @post event is logged
	 * @return void
	 */
	virtual void log(const std::string& text);
	/**
	 * Send finished message
	 * @param number of products made, time and machineId
	 * @pre machine is working
	 * @post machine is finished and ready for new work
	 * @return void
	 */
	virtual void finished(int nrOfOutput, time_duration time, int machineId);
	/**
	 * @brief sends simulationStopped message
	 * @param time current time
	 * @pre Message is not sent.
	 * @post Message is sent.
	 */
	virtual void simulationStopped(time_duration time);
	/**
	 *Send machineBroken message
	 *@param time that the machine broke on, machineId
	 *@pre machine is Working
	 *@post machine is Broken
	 *@return void
	 */
	virtual void machineBroken(time_duration time, int machineId);
	/**
	 * Enum for the diffent messageTypes a message can have.
	 */
	enum MessageType
	{
		OKMESSAGE, NOKMESSAGE, LOGMESSAGE, FINISHEDMESSAGE, MACHINEBROKENMESSAGE, SIMULATIONSTOPPEDMESSAGE
	};
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
	 * Whether the messagehandler is communicating
	 */
	bool communicating;
	inline bool isCommunicating()
	{
		return communicating;
	}

	void setProxyProductionControlPtr(
			ProxyProductionControl* proxyProductionControlPtr)
	{
		this->proxyProductionControlPtr = proxyProductionControlPtr;
	}

	//Pointer to the proxyProductionControl
	ProxyProductionControl* proxyProductionControlPtr;
	//network variables
	std::string localPort = "12345";
	std::string remoteIP = "localhost";
	std::string remotePort = "12344";
};

#endif /* EXE1_PROXYCONTROL_H_ */
