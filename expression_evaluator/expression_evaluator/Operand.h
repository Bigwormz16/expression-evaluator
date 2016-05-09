// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// Represents a numeric value to be used in an expression

#ifndef PSANDS_CISP430_OPERAND_H
#define PSANDS_CISP430_OPERAND_H

#include <string>

namespace psands_cisp430_a3
{
	class Operand
	{
	private:
		double _value;
	public:
		Operand();
		Operand(const double value);
		Operand(const Operand & operand);
		double getValue() const;
		void setValue(const double value);
		virtual std::string toString() const;

		Operand * operator+(const Operand & operand);
		Operand * operator-(const Operand & operand);
		Operand * operator*(const Operand & operand);
		Operand * operator/(const Operand & operand);

		Operand * sin();
		Operand * cos();
		Operand * sqrt();
		Operand * abs();
		Operand * negative();

		Operand * pow(const Operand & operand);
	};
}

#endif // PSANDS_CISP430_OPERAND_H