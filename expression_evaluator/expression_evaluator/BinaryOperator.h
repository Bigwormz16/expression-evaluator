#ifndef PSANDS_CISP430_BINARYOPERATOR_H
#define PSANDS_CISP430_BINARYOPERATOR_H

#include <functional>
#include "AbstractOperator.h"

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
		double Evaluate(psands_cisp430_a2::List<Operand *> * operands) override;
	};
}

#endif // PSANDS_CISP430_BINARYOPERATOR_H