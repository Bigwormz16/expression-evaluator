#include "Polynomial.h"
#include "PolynomialTerm.h"
#include "List.h"

psands_cisp430_a3::Polynomial::Polynomial()
{
	this->_terms = new psands_cisp430_a2::List<PolynomialTerm *>();
}

psands_cisp430_a3::Polynomial::~Polynomial()
{
}

void psands_cisp430_a3::Polynomial::add(PolynomialTerm * term)
{
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == term->canEvaluate() && true == lt->canEvaluate())
		{
		}
		
	}

	this->_terms->add(term);
}

void psands_cisp430_a3::Polynomial::subtract(PolynomialTerm * term)
{
}

void psands_cisp430_a3::Polynomial::multiply(PolynomialTerm * term)
{
}

std::string psands_cisp430_a3::Polynomial::toString() const
{
	return std::string();
}

bool psands_cisp430_a3::Polynomial::hasEvaluatedValue() const
{
	return false;
}

double psands_cisp430_a3::Polynomial::getEvaluatedValue() const
{
	return 0.0;
}