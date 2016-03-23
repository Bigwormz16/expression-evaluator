#include "UnaryOperator.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

UnaryOperator::UnaryOperator()
{
	this->_numberOfOperands = 1;
}

UnaryOperator::UnaryOperator(const std::function<double(double)>& operatorFunction) : UnaryOperator()
{
	this->operatorFunction = operatorFunction;
}

UnaryOperator::~UnaryOperator()
{
}

Operand * UnaryOperator::Evaluate(psands_cisp430_a2::List<Operand * >* operands)
{
	AbstractOperator::Evaluate(operands);

	Operand * result = new Operand(this->operatorFunction(operands->getElementAt(0)->getValue()));
	return result;
}
