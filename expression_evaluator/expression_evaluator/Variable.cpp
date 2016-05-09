#include "Variable.h"

psands_cisp430_a3::Variable::Variable() : Operand(0)
{
	this->_isInitialized = false;
}

psands_cisp430_a3::Variable::Variable(const std::string name) : Variable()
{
	this->_name = name;
}

psands_cisp430_a3::Variable::Variable(const std::string name, const double value) : Variable(name)
{
	this->setValue(value);
}

psands_cisp430_a3::Variable::Variable(const Variable & variable) : Variable(variable._name, variable.getValue())
{
	this->_isInitialized = variable._isInitialized;
}

void psands_cisp430_a3::Variable::setValue(const double value)
{
	Operand::setValue(value);
	this->_isInitialized = true;
}

std::string psands_cisp430_a3::Variable::toString() const
{
	if (true == this->_isInitialized)
	{
		return Operand::toString();
	}
	return this->_name;
}

bool psands_cisp430_a3::Variable::isInitialized() const
{
	return this->_isInitialized;
}
