// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "Operand.h"

using namespace psands_cisp430_a3;

Operand::Operand()
{
}

Operand::Operand(double value)
{
	this->_value = value;
}

Operand::~Operand()
{
}

double Operand::getValue()
{
	return this->_value;
}

void Operand::setValue(double value)
{
	this->_value = value;
}
