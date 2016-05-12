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
	bool shouldAdd = true;

	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == term->canEvaluate() && true == lt->canEvaluate())
		{
			double result = lt->getValue() + term->getValue();
			lt->setCoefficient(1);
			lt->setDblTerm(result);
			lt->setExponent(1);
			shouldAdd = false;
		}
		else if()
	}

	if (true == shouldAdd)
	{
		this->_terms->add(term);
	}
}

void psands_cisp430_a3::Polynomial::subtract(PolynomialTerm * term)
{
}

void psands_cisp430_a3::Polynomial::multiply(PolynomialTerm * term)
{
}

std::string psands_cisp430_a3::Polynomial::toString() const
{
	std::string result = "";
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		if ("" != result)
		{
			result += "+";
		}

		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == lt->canEvaluate())
		{
			result += " " + std::to_string(lt->getValue()) + " ";
		}
	}

	return result;
}

bool psands_cisp430_a3::Polynomial::hasEvaluatedValue() const
{
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		if (false == this->_terms->getElementAt(i)->canEvaluate())
		{
			return false;
		}
	}
	return true;
}

double psands_cisp430_a3::Polynomial::getEvaluatedValue() const
{
	double result = 0;
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		result += this->_terms->getElementAt(i)->getValue();
	}
	return result;
}