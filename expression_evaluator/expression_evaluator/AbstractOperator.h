// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#ifndef PSANDS_CISP430_ABSTRACTOPERATOR_H
#define PSANDS_CISP430_ABSTRACTOPERATOR_H

#include "List.h"
#include "Operand.h"

namespace psands_cisp430_a3
{
	class AbstractOperator
	{
	protected:
		unsigned int _numberOfOperands = 0;
	public:
		AbstractOperator();
		virtual ~AbstractOperator() = 0;
		virtual Operand * Evaluate(psands_cisp430_a2::List<Operand *> * operands);
	};
}

#endif // PSANDS_CISP430_ABSTRACTOPERATOR_H

