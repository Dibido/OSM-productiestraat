/*
 * Events.cpp
 *
 *  Created on: 20 nov. 2017
 *      Author: Stefan
 */

#include "Events.hpp"

Events::Events()
{
}

Events::~Events()
{
}

void Events::addEvent(boost::posix_time::time_duration time, const EventContent& event)
{
	DEBUG_MSG("added " << printEvent(time, event));
	eventList.insert(std::make_pair(time, event));
}

const std::pair<boost::posix_time::time_duration, EventContent> Events::getFirstEvent()
{
	return *(eventList.begin());
}

void Events::removeFirstEvent()
{
	DEBUG_MSG(__PRETTY_FUNCTION__ << " " << printEvent(eventList.begin()->first, eventList.begin()->second));
	eventList.erase(eventList.begin());
}

const std::string Events::printEvent(boost::posix_time::time_duration time, const EventContent& event) const
{
	// machine: " + std::to_string(event.machine->getConfig().id) + "
	std::string returnString = "\033[1;31mEvent: t:" + std::to_string(time.total_seconds() / 60) + " type: " + printEventType(event.eventType) + " hours: " + std::to_string(time.hours()) + "\033[0m";
	return returnString;
}
