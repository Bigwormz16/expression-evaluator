#ifndef PSANDS_CISP430_POLYNOMIALTERM_H
#define PSANDS_CISP430_POLYNOMIALTERM_H

#include "Token.h"

namespace psands_cisp430_a3
{
	class PolynomialTerm
	{
	private:
		double _coefficient;
		double _exponent;
		Token * _token;

	public:
		PolynomialTerm();
		PolynomialTerm(double coefficient, double exponent, Token * token);
		PolynomialTerm(const PolynomialTerm & polynomialTerm);

		double getCoefficient() const;
		double getExponent() const;
		Token * getToken() const;

		void setCoefficient(double coefficient);
		void setExponent(double exponent);
		void setToken(Token * token);

		// math functions
		bool canAdd(const PolynomialTerm & polynomialTerm);
		bool canSubtract(const PolynomialTerm & polynomialTerm);
		bool canMultiply(const PolynomialTerm & polynomialTerm);

		PolynomialTerm operator+(const PolynomialTerm & polynomialTerm);
		PolynomialTerm operator-(const PolynomialTerm & polynomialTerm);
		PolynomialTerm operator*(const PolynomialTerm & polynomialTerm);

	};
}


#endif // !PSANDS_CISP430_POLYNOMIALTERM_H