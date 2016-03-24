// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// inherits abstract operator, defines number of operands as 1, and takes a function to define 
//		the operation to perform

#ifndef PSANDS_CISP430_UNARYOPERATOR_H
#define PSANDS_CISP430_UNARYOPERATOR_H

#include <functional>
#include "AbstractOperator.h"
#include "Operand.h"

namespace psands_cisp430_a3
{
	class UnaryOperator :
		public AbstractOperator
	{
	private:
		std::function<double(double)> operatorFunction;
	public:
		UnaryOperator();
		UnaryOperator(const std::function<double(double)> & operatorFunction);
		~UnaryOperator();
		Operand * Evaluate(psands_cisp430_a2::List<Operand *> * operands) override;
	};
}

#endif // PSANDS_CISP430_UNARYOPERATOR_H