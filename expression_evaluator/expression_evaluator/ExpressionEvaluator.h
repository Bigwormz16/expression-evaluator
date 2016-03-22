#ifndef PSANDS_CISP430_EXPRESSIONEVALUATOR_H
#define PSANDS_CISP430_EXPRESSIONEVALUATOR_H

#include <fstream>
#include <string>
#include "InfixParser.h"
#include "Tokenizer.h"

namespace psands_cisp430_a3
{
	class ExpressionEvaluator
	{
	private:
		std::string _expression;
		InfixParser * _infixParser;
		Tokenizer * _tokenizer;
	public:
		ExpressionEvaluator();
		ExpressionEvaluator(std::string expression);
		~ExpressionEvaluator();
		void setExpression(std::string expression);
		double getExpressionResult();
		std::ostream & displayExpression(std::ostream & ostream);
	};
}

#endif // PSANDS_CISP430_EXPRESSIONEVALUATOR_H