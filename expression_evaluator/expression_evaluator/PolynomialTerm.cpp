#include <stdexcept>
#include "PolynomialTerm.h"
#include "Token.h"

using namespace psands_cisp430_a3;

psands_cisp430_a3::PolynomialTerm::PolynomialTerm()
{
	this->setCoefficient(0);
	this->setExponent(0);
	this->setToken(nullptr);
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(double coefficient, double exponent, Token * token)
{
	this->setCoefficient(coefficient);
	this->setExponent(exponent);
	this->setToken(token);
}

psands_cisp430_a3::PolynomialTerm::PolynomialTerm(const PolynomialTerm & polynomialTerm) : PolynomialTerm(polynomialTerm.getCoefficient(), polynomialTerm.getExponent(), polynomialTerm.getToken())
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

Token * psands_cisp430_a3::PolynomialTerm::getToken() const
{
	return this->_token;
}

void psands_cisp430_a3::PolynomialTerm::setCoefficient(double coefficient)
{
	this->_coefficient = coefficient;
}

void psands_cisp430_a3::PolynomialTerm::setExponent(double exponent)
{
	this->_exponent = exponent;
}

void psands_cisp430_a3::PolynomialTerm::setToken(Token * token)
{
	this->_token = token;
}

bool psands_cisp430_a3::PolynomialTerm::canAdd(const PolynomialTerm & polynomialTerm)
{
	if (this->getToken()->getTokenSymbol() == polynomialTerm.getToken()->getTokenSymbol() &&
		this->getExponent() == polynomialTerm.getExponent())
	{
		return true;
	}
	return false;
}

bool psands_cisp430_a3::PolynomialTerm::canSubtract(const PolynomialTerm & polynomialTerm)
{
	if (this->getToken()->getTokenSymbol() == polynomialTerm.getToken()->getTokenSymbol() &&
		this->getExponent() == polynomialTerm.getExponent())
	{
		return true;
	}
	return false;
}

bool psands_cisp430_a3::PolynomialTerm::canMultiply(const PolynomialTerm & polynomialTerm)
{
	if (this->getToken()->getTokenSymbol() == polynomialTerm.getToken()->getTokenSymbol())
	{
		return true;
	}
	return false;
}

PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator+(const PolynomialTerm & polynomialTerm)
{
	if (false == this->canAdd(polynomialTerm))
	{
		throw std::invalid_argument("unable to perform addition operation on polynomial term provided.");
	}

	PolynomialTerm result = PolynomialTerm(this->getCoefficient() + polynomialTerm.getCoefficient(), this->getExponent(), this->getToken());
	return result;
}

PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator-(const PolynomialTerm & polynomialTerm)
{
	if (false == this->canSubtract(polynomialTerm))
	{
		throw std::invalid_argument("unable to perform subtraction operation on polynomial term provided.");
	}

	PolynomialTerm result = PolynomialTerm(this->getCoefficient() - polynomialTerm.getCoefficient(), this->getExponent(), this->getToken());
	return result;
}

PolynomialTerm psands_cisp430_a3::PolynomialTerm::operator*(const PolynomialTerm & polynomialTerm)
{
	if (false == this->canMultiply(polynomialTerm))
	{
		throw std::invalid_argument("unable to perform multiplication operation on polynomial term provided.");
	}

	PolynomialTerm result = PolynomialTerm(this->getCoefficient() * polynomialTerm.getCoefficient(), this->getExponent() + polynomialTerm.getExponent(), this->getToken());
	return result;
}
