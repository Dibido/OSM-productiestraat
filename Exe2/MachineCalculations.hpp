/*
 * MachineCalculations.hpp
 *
 *  Created on: 28 nov. 2017
 *      Author: Stefan
 */

#ifndef EXE2_MACHINECALCULATIONS_HPP_
#define EXE2_MACHINECALCULATIONS_HPP_

#include "../Exe2/MachineConfig.hpp"

class MachineCalculations
{
public:
	MachineCalculations();
	virtual ~MachineCalculations();
	/**
	 * @brief calculates the nr of parts that were made.(quick maths)
	 * @param inputAmount amount of parts given to machine
	 * @param aConfig config of machine
	 * @pre currentAmountOfWork is set
	 * @post returns result
	 * @return nr. of produced parts
	 */
	static int calculateOutputParts(int inputAmount, const MachineConfig& aConfig);
	/**
	 * @brief calculates the process time in seconds.(quick maths)
	 * @param inputAmount amount of parts given to machine
	 * @param aConfig config of machine
	 * @pre currentAmountOfWork is set
	 * @post returns result
	 * @return the time in seconds that the machine needs to process the parts
	 */
	static int calculateProcessTime(int inputAmount, const MachineConfig& aConfig);


private:
};

#endif /* EXE1_MACHINECALCULATIONS_HPP_ */
