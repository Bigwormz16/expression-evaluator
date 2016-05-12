#include "Variable.h"
#include "Polynomial.h"

psands_cisp430_a3::Variable::Variable(const std::string name)
{
	this->_name = name;
	this->_isInitialized = false;
	this->_polynomial = nullptr;
}

psands_cisp430_a3::Variable::Variable(const std::string name, Polynomial * polynomial)
{
	this->_name = name;
	this->_isInitialized = (nullptr != this->_polynomial);
	this->_polynomial = polynomial;
}

psands_cisp430_a3::Variable::Variable(const Variable & variable)
	: Variable(variable._name, variable._polynomial)
{
}

psands_cisp430_a3::Polynomial * psands_cisp430_a3::Variable::getValue() const
{
	return this->_polynomial;
}

void psands_cisp430_a3::Variable::setValue(Polynomial * value)
{
	this->_polynomial = value;
}

std::string psands_cisp430_a3::Variable::toString() const
{
	if (false == this->_isInitialized || nullptr == this->_polynomial)
	{
		return this->_name;
	}
	return this->_polynomial->toString();
}

bool psands_cisp430_a3::Variable::isInitialized() const
{
	return this->_isInitialized;
}

bool psands_cisp430_a3::Variable::hasEvaluatedValue() const
{
	return true == this->_isInitialized && nullptr != this->_polynomial && true == this->_polynomial->hasEvaluatedValue();
}

double psands_cisp430_a3::Variable::getEvaluatedValue() const
{
	if (true == this->hasEvaluatedValue())
	{
		return this->_polynomial->getEvaluatedValue();
	}
	return 0;
}

std::string psands_cisp430_a3::Variable::getName()
{
	return this->_name;
}
