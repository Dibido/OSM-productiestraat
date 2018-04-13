/*
 * Events.hpp
 *
 *  Created on: 20 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_EVENTS_HPP_
#define EXE2_EVENTS_HPP_

#include <boost/date_time/posix_time/posix_time_config.hpp>
#include <map>
#include <iostream>
#include <string>
#include <utility>

#include "Defines.hpp"
#include "EventContent.hpp"

/**
 * @brief class with eventlist and functions to get and add events
 */
class Events
{
public:
	Events();
	virtual ~Events();
	/**
	 * @brief adds an event to the event list.
	 * @param time time that the event will occur
	 * @param event eventType and machine adress
	 * @pre -
	 * @post event is added to list
	 */
	//cppcheck-suppress functionStatic
	void addEvent(boost::posix_time::time_duration time, const EventContent& event);

	/**
	 * @brief gets the first event from the eventlist
	 * @pre eventlist is not empty
	 * @post getter..
	 * @return a pair with time and event
	 */
	const std::pair<boost::posix_time::time_duration, EventContent> getFirstEvent();
	/**
	 * @brief removes first element from eventlist
	 * @pre -
	 * @post first event is deleted
	 */
	void removeFirstEvent();
	/**
	 * @brief Function that converts the event so it can print. EventContent -> string
	 * @param time time of that the event occurs
	 * @param event The event that needs to be converted
	 * @pre -
	 * @post event is converted to string
	 * @return String representation of the event
	 */
	//cppcheck-suppress functionStatic
	const std::string printEvent(boost::posix_time::time_duration time, const EventContent& event) const;

	/**
	 * @brief function for printing the type of the event.
	 * @param event time/eventContent
	 * @pre -
	 * @post eventType is converted to string
	 * @return string with textual representation of event
	 */
	static const std::string printEventType(EventType event)
	{
		return EventTypeToString.at(event);
	}

private:
	std::multimap<boost::posix_time::time_duration, EventContent> eventList;
};

#endif /* EXE1_EVENTS_HPP_ */
