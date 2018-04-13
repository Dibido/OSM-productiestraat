/*
 * MachineState.hpp
 *
 *  Created on: 29 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_MACHINESTATE_HPP_
#define EXE2_MACHINESTATE_HPP_


/**
 * @brief struct with states of machine
 */
enum struct MachineState
{
	BROKEN,//!< BROKEN
	BUSY,  //!< BUSY
	ON,    //!< ON
	OFF,   //!< OFF
	INIT   //!< INIT
};

/**
 * @brief map for converting MachineState to string
 */
static std::map<MachineState, std::string> MachineStateToString = {
		std::make_pair(MachineState::BROKEN, "BROKEN"),
		std::make_pair(MachineState::BUSY, "BUSY"),
		std::make_pair(MachineState::ON, "ON"),
		std::make_pair(MachineState::OFF, "OFF"),
		std::make_pair(MachineState::INIT, "INIT"),
};

#endif /* EXE1_MACHINESTATE_HPP_ */
