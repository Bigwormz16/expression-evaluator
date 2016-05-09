// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "Operand.h"
#include <cmath>

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

Operand * psands_cisp430_a3::Operand::operator+(const Operand & operand)
{
	return new Operand(this->getValue() + operand.getValue());
}

Operand * psands_cisp430_a3::Operand::operator-(const Operand & operand)
{
	return new Operand(this->getValue() - operand.getValue());
}

Operand * psands_cisp430_a3::Operand::operator*(const Operand & operand)
{
	return new Operand(this->getValue() * operand.getValue());
}

Operand * psands_cisp430_a3::Operand::operator/(const Operand & operand)
{
	return new Operand(this->getValue() / operand.getValue());
}

Operand * psands_cisp430_a3::Operand::sin()
{
	return new Operand(std::sin(this->getValue()));
}

Operand * psands_cisp430_a3::Operand::cos()
{
	return new Operand(std::cos(this->getValue()));
}

Operand * psands_cisp430_a3::Operand::sqrt()
{
	return new Operand(std::sqrt(this->getValue()));
}

Operand * psands_cisp430_a3::Operand::abs()
{
	return new Operand(std::abs(this->getValue()));
}

Operand * psands_cisp430_a3::Operand::negative()
{
	return new Operand(this->getValue() * -1);
}

Operand * psands_cisp430_a3::Operand::pow(const Operand & operand)
{
	return new Operand(std::pow(this->getValue(), operand.getValue()));
}
