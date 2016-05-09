// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "UnaryOperator.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

UnaryOperator::UnaryOperator()
{
	this->_numberOfOperands = 1;
}

UnaryOperator::UnaryOperator(const std::function<Operand *(Operand *)>& operatorFunction) : UnaryOperator()
{
	this->operatorFunction = operatorFunction;
}

UnaryOperator::~UnaryOperator()
{
}

Operand * UnaryOperator::Evaluate(List<Operand * >* operands)
{
	AbstractOperator::Evaluate(operands);

	Operand * result = this->operatorFunction(operands->getElementAt(0));
	return result;
}
