/*
 * ConcreteState.hpp
 *
 *  Created on: 26 sep. 2016
 *      Author: stefa
 */

#ifndef CONCRETESTATE_HPP_
#define CONCRETESTATE_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

#include "../../Exe1/IniParser/IniParser.hpp"

#include "Defines.hpp"
#include "AbstractState.hpp"
#include "Machine.hpp"
#include "MachineConfig.hpp"

struct EventContent;

class AbstractMachineState: public AbstractState
{
public:
	explicit AbstractMachineState(Machine* aMachine) :
		AbstractState(aMachine)
	{
	}
	Machine* getMachine();
};

// -- STATES -- //


class OffState: public AbstractMachineState
{
public:
	explicit OffState(Machine* aMachine = nullptr);
	void entry();
	void doActivity();
	void exit();
	bool handleEvent(const EventContent& aEV);
	virtual ~OffState();
private:

};

class InitState: public AbstractMachineState
{
public:
	explicit InitState(Machine* aMachine = nullptr);
	void entry();
	void doActivity();
	void exit();
	bool handleEvent(const EventContent& aEV);
	virtual ~InitState();
private:

};

class OnState: public AbstractMachineState
{
public:
	explicit OnState(Machine* aMachine = nullptr);
	void entry();
	void doActivity();
	void exit();
	bool handleEvent(const EventContent& aEV);
	virtual ~OnState();
private:

};

class BusyState: public AbstractMachineState
{
public:
	explicit BusyState(Machine* aMachine = nullptr);
	void entry();
	void doActivity();
	void exit();
	bool handleEvent(const EventContent& aEV);
	virtual ~BusyState();
private:

};

class BrokenState: public AbstractMachineState
{
public:
	explicit BrokenState(Machine* aMachine = nullptr);
	void entry();
	void doActivity();
	void exit();
	bool handleEvent(const EventContent& aEV);
	virtual ~BrokenState();
private:

};

#endif /* CONCRETESTATE_HPP_ */
