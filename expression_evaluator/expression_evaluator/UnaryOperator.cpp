#include "UnaryOperator.h"

psands_cisp430_a3::UnaryOperator::UnaryOperator()
{
	this->_numberOfOperands = 1;
}

psands_cisp430_a3::UnaryOperator::UnaryOperator(const std::function<double(double)>& operatorFunction) : UnaryOperator()
{
	this->operatorFunction = operatorFunction;
}

psands_cisp430_a3::UnaryOperator::~UnaryOperator()
{
}

double psands_cisp430_a3::UnaryOperator::Evaluate(psands_cisp430_a2::List<double>* operands)
{
	AbstractOperator::Evaluate(operands);

	return this->operatorFunction(operands->getElementAt(0));
}
