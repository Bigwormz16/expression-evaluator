#include <stdexcept>
#include "PolynomialTerm.h"
#include "Operand.h"
#include "Variable.h"
#include <cmath>

using namespace psands_cisp430_a3;

psands_cisp430_a3::PolynomialTerm::PolynomialTerm() : PolynomialTerm(0, 0, nullptr)
{
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const double coefficient, const double exponent, Operand * operand)
{
	this->setCoefficient(coefficient);
	this->setExponent(exponent);
	this->setOperand(operand);
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const PolynomialTerm & polynomialTerm)
	: PolynomialTerm(polynomialTerm.getCoefficient(), polynomialTerm.getExponent(), polynomialTerm.getOperand())
{
}

double psands_cisp430_a3::PolynomialTerm::getCoefficient() const
{
	return this->_coefficient;
}

double psands_cisp430_a3::PolynomialTerm::getExponent() const
{
	return this->_exponent;
}

Operand * psands_cisp430_a3::PolynomialTerm::getOperand() const
{
	return this->_operand;
}

void psands_cisp430_a3::PolynomialTerm::setCoefficient(const double coefficient)
{
	this->_coefficient = coefficient;
}

void psands_cisp430_a3::PolynomialTerm::setExponent(const double exponent)
{
	this->_exponent = exponent;
}

void psands_cisp430_a3::PolynomialTerm::setOperand(Operand * operand)
{
	this->_operand = operand;
}

bool psands_cisp430_a3::PolynomialTerm::canEvaluate()
{
	Variable * var = (Variable *) this->getOperand();
	return var->isInitialized();
}

double psands_cisp430_a3::PolynomialTerm::getValue()
{
	return std::pow(this->getOperand()->getValue(), this->getExponent()) * this->getCoefficient();
}


PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator+(const PolynomialTerm & polynomialTerm)
{
	PolynomialTerm result = PolynomialTerm(this->getCoefficient() + polynomialTerm.getCoefficient(), this->getExponent(), this->getOperand());
	return result;
}

PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator-(const PolynomialTerm & polynomialTerm)
{
	PolynomialTerm result = PolynomialTerm(this->getCoefficient() - polynomialTerm.getCoefficient(), this->getExponent(), this->getOperand());
	return result;
}

PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator*(const PolynomialTerm & polynomialTerm)
{
	PolynomialTerm result = PolynomialTerm(this->getCoefficient() * polynomialTerm.getCoefficient(), this->getExponent() + polynomialTerm.getExponent(), this->getOperand());
	return result;
}

std::string psands_cisp430_a3::PolynomialTerm::toString() const
{
	return std::to_string(this->getCoefficient()) + " * " + this->getOperand()->toString() + " ^ " + std::to_string(this->getExponent());
}
