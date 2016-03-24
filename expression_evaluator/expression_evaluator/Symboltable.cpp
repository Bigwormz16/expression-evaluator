// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "Symboltable.h"
#include <string>
#include "Operand.h"

using namespace psands_cisp430;
using namespace psands_cisp430_a3;

int Symboltable::hashFunction(std::string key)
{
	int hashValue = 15;

	for (unsigned int i = 0; i < key.length(); i++)
	{
		if (0 == i % 2)
		{
			hashValue += key.at(i);
		}
	}

	hashValue = hashValue % this->getPrimaryBucketCount();

	return hashValue;
}

Symboltable::Symboltable() : Hashtable<std::string, Operand *>()
{
}

Symboltable::Symboltable(int maxBucket, int maxSlots, int maxOverflowBuckets) : Hashtable<std::string, Operand *>(maxBucket, maxSlots, maxOverflowBuckets)
{
}


Symboltable::~Symboltable()
{
}