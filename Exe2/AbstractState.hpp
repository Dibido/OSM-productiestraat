/*
 * AbstractState.hpp
 *
 *  Created on: 26 sep. 2016
 *      Author: stefa
 */

#ifndef ABSTRACTSTATE_HPP_
#define ABSTRACTSTATE_HPP_
#include "AbstractEventHandler.hpp"

class Machine;

class AbstractState : public AbstractEventHandler
{
public:
	/**
	 * @brief /entry of the state
	 * @param aMachine machine
	 */
	explicit AbstractState(Machine* aMachine=nullptr):myMachine(aMachine){};
	/**
	 * @brief /exit of the state;
	 */
	virtual void entry() = 0;
	/**
	 * @brief /do of the state
	 */
	virtual void doActivity() =0;
	/**
	 * @brief /exit of the state;
	 */
	virtual void exit() = 0;
	/**
	 * @brief function that is called by some states
	 */
	void eventTURNOFF();
	/**
	 * @brief function that is called by some states
	 */
	void eventREPAIRED();
	/**
	 * @brief function that is called by some states
	 */
	void eventISBROKEN();
	/**
	 * @brief /exit of the state
	 */
	virtual ~AbstractState(){};
	Machine* getMachine() {return myMachine;}
protected:
	Machine* myMachine;
};

#endif /* ABSTRACTSTATE_HPP_ */
