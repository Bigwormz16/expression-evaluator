// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "BinaryOperator.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

BinaryOperator::BinaryOperator()
{
	this->_numberOfOperands = 2;
}

BinaryOperator::BinaryOperator(const std::function<double(double, double)>& operatorFunction) : BinaryOperator()
{
	this->operatorFunction = operatorFunction;
}

BinaryOperator::~BinaryOperator()
{
}

Operand * BinaryOperator::Evaluate(List<Operand *> * operands)
{
	AbstractOperator::Evaluate(operands);

	// operand elements are arriving in reverse order due to the behavior of postfix evaluation stack
	Operand * result = new Operand(this->operatorFunction(operands->getElementAt(1)->getValue(), operands->getElementAt(0)->getValue()));
	return result;
}
