#include "Operand.h"

psands_cisp430_a3::Operand::Operand()
{
}

psands_cisp430_a3::Operand::Operand(double value)
{
	this->_value = value;
}

psands_cisp430_a3::Operand::~Operand()
{
}

double psands_cisp430_a3::Operand::getValue()
{
	return this->_value;
}
