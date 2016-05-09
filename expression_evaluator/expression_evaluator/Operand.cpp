// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "Operand.h"

using namespace psands_cisp430_a3;

Operand::Operand()
{
}

Operand::Operand(const double value)
{
	this->_value = value;
}

psands_cisp430_a3::Operand::Operand(const Operand & operand) : Operand(operand.getValue())
{
}

double psands_cisp430_a3::Operand::getValue() const
{
	return this->_value;
}

void Operand::setValue(const double value)
{
	this->_value = value;
}

std::string psands_cisp430_a3::Operand::toString() const
{
	return std::to_string(this->getValue());
}
