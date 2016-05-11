#ifndef PSANDS_CISP430_POLYNOMIAL_H
#define PSANDS_CISP430_POLYNOMIAL_H

#include "List.h"
#include <string>

namespace psands_cisp430_a3
{
	class PolynomialTerm;

	class Polynomial
	{
	private:
		psands_cisp430_a2::List<PolynomialTerm *> * _terms;
	public:
		Polynomial();
		~Polynomial();
		void add(PolynomialTerm * term);
		void subtract(PolynomialTerm * term);
		void multiply(PolynomialTerm * term);
		std::string toString() const;

		bool hasEvaluatedValue() const;
		double getEvaluatedValue() const;
	};
}

#endif // !PSANDS_CISP430_POLYNOMIAL_H