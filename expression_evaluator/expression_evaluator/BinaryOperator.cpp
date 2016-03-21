#include "BinaryOperator.h"

psands_cisp430_a3::BinaryOperator::BinaryOperator()
{
	this->_numberOfOperands = 2;
}

psands_cisp430_a3::BinaryOperator::BinaryOperator(const std::function<double(double, double)>& operatorFunction) : BinaryOperator()
{
	this->operatorFunction = operatorFunction;
}

psands_cisp430_a3::BinaryOperator::~BinaryOperator()
{
}

double psands_cisp430_a3::BinaryOperator::Evaluate(psands_cisp430_a2::List<Operand *> * operands)
{
	AbstractOperator::Evaluate(operands);

	return this->operatorFunction(operands->getElementAt(0)->getValue(), operands->getElementAt(1)->getValue());
}
