// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// Represents a map of a variable name to an address of an operand.
//		Facilitates retrieval of addresses by variable name for getting and setting the operand value

#ifndef PSANDS_CISP430_SYMBOLTABLE_H
#define PSANDS_CISP430_SYMBOLTABLE_H

#include <string>
#include "Hashtable.h"
#include "Operand.h"

namespace psands_cisp430_a3
{
	class Symboltable :
		public psands_cisp430::Hashtable<std::string, Operand *>
	{
	protected:
		int hashFunction(std::string key) override;
	public:
		Symboltable();
		Symboltable(int maxBucket, int maxSlots, int maxOverflowBuckets);
		~Symboltable();
	};
}

#endif // PSANDS_CISP430_SYMBOLTABLE_H