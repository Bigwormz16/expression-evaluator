#ifndef PSANDS_CISP430_UNARYOPERATOR_H
#define PSANDS_CISP430_UNARYOPERATOR_H

#include <functional>
#include "AbstractOperator.h"

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
		double Evaluate(psands_cisp430_a2::List<double> * operands) override;
	};
}

#endif // PSANDS_CISP430_UNARYOPERATOR_H