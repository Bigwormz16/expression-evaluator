#include <stdexcept>
#include "PolynomialTerm.h"
#include "Variable.h"
#include <cmath>

using namespace psands_cisp430_a3;


//PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator+(const PolynomialTerm & polynomialTerm)
//{
//	PolynomialTerm result = PolynomialTerm(this->getCoefficient() + polynomialTerm.getCoefficient(), this->getExponent(), this->getOperand());
//	return result;
//}
//
//PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator-(const PolynomialTerm & polynomialTerm)
//{
//	PolynomialTerm result = PolynomialTerm(this->getCoefficient() - polynomialTerm.getCoefficient(), this->getExponent(), this->getOperand());
//	return result;
//}
//
//PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator*(const PolynomialTerm & polynomialTerm)
//{
//	PolynomialTerm result = PolynomialTerm(this->getCoefficient() * polynomialTerm.getCoefficient(), this->getExponent() + polynomialTerm.getExponent(), this->getOperand());
//	return result;
//}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm()
{
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const double dblTerm)
	: PolynomialTerm(1, 1, dblTerm)
{
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const double coefficient, const double exponent, const double dblTerm)
{
	this->setCoefficient(coefficient);
	this->setExponent(exponent);
	this->setDblTerm(dblTerm);
	this->_hasDblTerm = true;
	this->setVarTerm(nullptr);
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const double coefficient, const double exponent, Variable * variable)
{
	this->setCoefficient(coefficient);
	this->setExponent(exponent);
	this->setVarTerm(variable);
	this->_hasDblTerm = false;
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const PolynomialTerm & polynomialTerm)
{
	this->setCoefficient(polynomialTerm.getCoefficient());
	this->setExponent(polynomialTerm.getExponent());
	this->setDblTerm(polynomialTerm.getDblTerm());
	this->setVarTerm(polynomialTerm.getVarTerm());
	this->_hasDblTerm = polynomialTerm.hasDoubleTerm();
}

double psands_cisp430_a3::PolynomialTerm::getCoefficient() const
{
	return this->_coefficient;
}

double psands_cisp430_a3::PolynomialTerm::getExponent() const
{
	return this->_exponent;
}

Variable * psands_cisp430_a3::PolynomialTerm::getVarTerm() const
{
	return this->_varTerm;
}

double psands_cisp430_a3::PolynomialTerm::getDblTerm() const
{
	return this->_dblTerm;
}

bool psands_cisp430_a3::PolynomialTerm::hasDoubleTerm() const
{
	return this->_hasDblTerm;
}

void psands_cisp430_a3::PolynomialTerm::setCoefficient(const double coefficient)
{
	this->_coefficient = coefficient;
}

void psands_cisp430_a3::PolynomialTerm::setExponent(const double exponent)
{
	this->_exponent = exponent;
}

void psands_cisp430_a3::PolynomialTerm::setVarTerm(Variable * varTerm)
{
	this->_varTerm = varTerm;
}

void psands_cisp430_a3::PolynomialTerm::setDblTerm(const double dblTerm)
{
	this->_dblTerm = dblTerm;
}

bool psands_cisp430_a3::PolynomialTerm::canEvaluate()
{
	return this->hasDoubleTerm() || (nullptr != this->_varTerm && true == this->_varTerm->hasEvaluatedValue());
}

double psands_cisp430_a3::PolynomialTerm::getValue()
{
	if (true == this->canEvaluate())
	{
		if (true == this->hasDoubleTerm())
		{
			return this->getExponent() * std::pow(this->getDblTerm(), this->getExponent());
		}
		else if (nullptr != this->getVarTerm() && true == this->getVarTerm()->hasEvaluatedValue())
		{
			return this->getVarTerm()->getEvaluatedValue();
		}
	}	
	return 0;
}

std::string psands_cisp430_a3::PolynomialTerm::toString()
{
	if (true == this->canEvaluate())
	{
		return std::to_string(this->getValue());
	}
	return std::to_string(this->getExponent()) + " * (" + this->getVarTerm()->toString() + ") ^ " + std::to_string(this->getExponent());
}

bool psands_cisp430_a3::PolynomialTerm::canAdd(PolynomialTerm * term)
{
	if (nullptr != term && nullptr != this)
	{
		if (true == this->canEvaluate() &&
			true == term->canEvaluate())
		{
			return true;
		}
		else if((true == this->canEvaluate() && )
	}
}

bool psands_cisp430_a3::PolynomialTerm::canSubtract(PolynomialTerm * term)
{
	return false;
}

bool psands_cisp430_a3::PolynomialTerm::canMultiply(PolynomialTerm * term)
{
	return false;
}
