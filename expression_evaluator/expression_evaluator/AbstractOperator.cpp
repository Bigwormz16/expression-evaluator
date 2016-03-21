#include <stdexcept>
#include "AbstractOperator.h"

psands_cisp430_a3::AbstractOperator::AbstractOperator()
{
}

psands_cisp430_a3::AbstractOperator::~AbstractOperator()
{
}

double psands_cisp430_a3::AbstractOperator::Evaluate(psands_cisp430_a2::List<Operand *> * operands)
{
	if (this->_numberOfOperands != operands->getCount())
	{
		throw std::invalid_argument("Not enough operands provided.");
	}
}
