/*
 * AbstractEventHandler.hpp
 *
 *  Created on: 12 sep. 2016
 *      Author: stefa
 */

#ifndef ABSTRACTEVENTHANDLER_HPP_
#define ABSTRACTEVENTHANDLER_HPP_

#include "EventContent.hpp"


class AbstractEventHandler
{
public:
	virtual ~AbstractEventHandler() {};
	/**
	 * @brief event will be handled by derived class: state
	 * @param aEV event that occurs
	 * @pre -
	 * @post event is handled
	 * @return true if event is successfully handled
	 */
	virtual bool handleEvent(const EventContent& aEV) =0;	// =0 is pure virtual
};

#endif /* ABSTRACTEVENTHANDLER_HPP_ */
