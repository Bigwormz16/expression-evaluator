// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#ifndef PSANDS_CISP430_BINARYOPERATOR_H
#define PSANDS_CISP430_BINARYOPERATOR_H

#include <functional>
#include "AbstractOperator.h"
#include "Operand.h"

namespace psands_cisp430_a3
{
	class BinaryOperator :
		public AbstractOperator
	{
	private:
		std::function<double(double, double)> operatorFunction;
	public:
		BinaryOperator();
		BinaryOperator(const std::function<double(double, double)> & operatorFunction);
		~BinaryOperator();
		Operand * Evaluate(psands_cisp430_a2::List<Operand *> * operands) override;
	};
}

#endif // PSANDS_CISP430_BINARYOPERATOR_H