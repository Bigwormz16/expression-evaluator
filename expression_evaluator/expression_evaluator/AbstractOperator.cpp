// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include <stdexcept>
#include "AbstractOperator.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

AbstractOperator::AbstractOperator()
{
}

AbstractOperator::~AbstractOperator()
{
}

Operand * AbstractOperator::Evaluate(List<Operand *> * operands)
{
	if (this->_numberOfOperands != operands->getCount())
	{
		throw std::invalid_argument("Not enough operands provided.");
	}
}
