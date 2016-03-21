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
		virtual double Evaluate(psands_cisp430_a2::List<Operand *> * operands);
	};
}

#endif // PSANDS_CISP430_ABSTRACTOPERATOR_H

