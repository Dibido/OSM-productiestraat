/*
 * EventContent.hpp
 *
 *  Created on: 17 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_EVENTCONTENT_HPP_
#define EXE2_EVENTCONTENT_HPP_

#include <map>

class Machine;

/**
 * @brief event types of system
 */
enum struct EventType
{
	FINISHEDWORK,      //!< FINISHEDWORK
	REPAIRED,          //!< REPAIRED
	ISBROKEN,          //!< ISBROKEN
	FINISHEDINIT,      //!< FINISHEDINIT
	FINISHEDSIMULATION,//!< FINISHEDSIMULATION
	STARTWORK,         //!< STARTWORK
	TURNON,            //!< TURNON
	TURNOFF            //!< TURNOFF
};
/**
 * @brief map for converting events to string
 */
static std::map<EventType, std::string> EventTypeToString = {
		std::make_pair(EventType::FINISHEDWORK, "FINISHEDWORK"),
		std::make_pair(EventType::REPAIRED, "REPAIRED"),
		std::make_pair(EventType::ISBROKEN, "ISBROKEN"),
		std::make_pair(EventType::FINISHEDINIT, "FINISHEDINIT"),
		std::make_pair(EventType::FINISHEDSIMULATION, "FINISHEDSIMULATION"),
		std::make_pair(EventType::STARTWORK, "STARTWORK"),
		std::make_pair(EventType::TURNON, "TURNON"),
		std::make_pair(EventType::TURNOFF, "TURNOFF"),
};

/**
 * @brief struct with machine* and eventType
 */
struct EventContent
{
	Machine* machine;
	EventType eventType;
};

#endif /* EXE1_EVENTCONTENT_HPP_ */
