#include "Polynomial.h"
#include "PolynomialTerm.h"
#include "List.h"
#include <string>

using namespace std;
using namespace psands_cisp430_a2;

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
		if (true == lt->canAdd(term))
		{
			lt->add(term);

			if (0 == lt->getCoefficient())
			{
				this->_terms->remove(lt);
			}

			return;
		}
	}
	if (0 != term->getCoefficient())
	{
		this->_terms->add(term);
	}
}

void psands_cisp430_a3::Polynomial::subtract(PolynomialTerm * term)
{
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == lt->canSubtract(term))
		{
			lt->subtract(term);

			if (0 == lt->getCoefficient())
			{
				this->_terms->remove(lt);
			}

			return;
		}
	}
	if (0 != term->getCoefficient())
	{
		this->_terms->add(term);
	}
}

void psands_cisp430_a3::Polynomial::multiply(PolynomialTerm * term)
{
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == lt->canMultiply(term))
		{
			lt->multiply(term);

			if (0 == lt->getCoefficient())
			{
				this->_terms->remove(lt);
			}

			return;
		}
	}

	if (0 != term->getCoefficient())
	{
		this->_terms->add(term);
	}
}

std::string psands_cisp430_a3::Polynomial::toString() const
{
	std::string result = "";
	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		if ("" != result)
		{
			result += " + ";
		}

		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (true == lt->canEvaluate())
		{
			result += " " + std::to_string(lt->getValue()) + " ";
		}
		else
		{
			result += lt->toString();
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

bool psands_cisp430_a3::Polynomial::isTerm()
{
	return nullptr != this && nullptr != this->_terms && 1 == this->_terms->getCount();
}

psands_cisp430_a3::PolynomialTerm * psands_cisp430_a3::Polynomial::getTerm()
{
	return this->_terms->getElementAt(0);
}

std::string psands_cisp430_a3::Polynomial::getDegree() const
{
	List<PolynomialTerm *> * degrees = new List<PolynomialTerm *>();

	for (int i = 0; i < this->_terms->getCount(); i++)
	{
		PolynomialTerm * lt = this->_terms->getElementAt(i);
		if (false == lt->canEvaluate())
		{
			bool isInDegrees = false;
			for (int j = 0; j < degrees->getCount(); j++)
			{
				PolynomialTerm * dt = degrees->getElementAt(j);
				if (lt->getVarTerm()->getName() == dt->getVarTerm()->getName())
				{
					isInDegrees = true;
					if (lt->getExponent() > dt->getExponent())
					{
						degrees->remove(dt);
						degrees->insert(lt, j);
					}
				}
			}
			if (false == isInDegrees)
			{
				degrees->add(lt);
			}
		}		
	}

	std::string result = "";
	for (int i = 0; i < degrees->getCount(); i++)
	{
		PolynomialTerm * lt = degrees->getElementAt(i);
		result += "{ " + lt->getVarTerm()->getName() + ", " + std::to_string(lt->getExponent()) + " }    ";
	}
	return result;
}
