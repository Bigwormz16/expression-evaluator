#ifndef PSANDS_CISP430_VARIABLE_H
#define PSANDS_CISP430_VARIABLE_H

#include <string>
#include "Polynomial.h"

namespace psands_cisp430_a3
{
	class Variable
	{
	private:
		bool _isInitialized;
		std::string _name; // the name of the variable
		Polynomial * _polynomial; // the value stored in the variable
	public:
		Variable(const std::string name);
		Variable(const std::string name, Polynomial * polynomial);
		Variable(const Variable & variable);
		Polynomial * getValue() const;
		void setValue(Polynomial * value);
		virtual std::string toString() const;
		bool isInitialized() const;
		bool hasEvaluatedValue() const;
		double getEvaluatedValue() const;
		std::string getName();
	};
}

#endif // !PSANDS_CISP430_VARIABLE_H