#ifndef PSANDS_CISP430_VARIABLE_H
#define PSANDS_CISP430_VARIABLE_H

#include "Operand.h"
#include <string>

namespace psands_cisp430_a3
{
	class Variable :
		public Operand
	{
	private:
		bool _isInitialized;
		std::string _name;
	public:
		Variable();
		Variable(const std::string name);
		Variable(const std::string name, const double value);
		Variable(const Variable & variable);
		void setValue(const double value);
		virtual std::string toString() const override;
		bool isInitialized() const;
	};
}

#endif // !PSANDS_CISP430_VARIABLE_H