#ifndef PSANDS_CISP430_POLYNOMIALTERM_H
#define PSANDS_CISP430_POLYNOMIALTERM_H

#include <string>
#include "Variable.h"

namespace psands_cisp430_a3
{
	class PolynomialTerm
	{
	private:
		double _coefficient;
		double _exponent;
		
		Variable * _varTerm;
		double _dblTerm;

		bool _hasDblTerm;

	public:
		PolynomialTerm();
		PolynomialTerm(const double dblTerm);
		PolynomialTerm(const double coefficient, const double exponent, const double dblTerm);
		PolynomialTerm(const double coefficient, const double exponent, Variable * variable);
		PolynomialTerm(const PolynomialTerm & polynomialTerm);

		double getCoefficient() const;
		double getExponent() const;
		Variable * getVarTerm() const;
		double getDblTerm() const;
		bool hasDoubleTerm() const;

		void setCoefficient(const double coefficient);
		void setExponent(const double exponent);
		void setVarTerm(Variable * varTerm);
		void setDblTerm(const double dblTerm);

		bool canEvaluate();
		double getValue();

		//PolynomialTerm operator+(const PolynomialTerm & polynomialTerm);
		//PolynomialTerm operator-(const PolynomialTerm & polynomialTerm);
		//PolynomialTerm operator*(const PolynomialTerm & polynomialTerm);

		virtual std::string toString();

		bool canAdd(PolynomialTerm * term);
		bool canSubtract(PolynomialTerm * term);
		bool canMultiply(PolynomialTerm * term);
	};
}


#endif // !PSANDS_CISP430_POLYNOMIALTERM_H