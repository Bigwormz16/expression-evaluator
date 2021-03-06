// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// Uses the other modules created for assignment 3 to convert an infix expression to postfix,
//		evaluate the expression, and potentially assign the evaluation to a variable

#ifndef PSANDS_CISP430_EXPRESSIONEVALUATOR_H
#define PSANDS_CISP430_EXPRESSIONEVALUATOR_H

#include <fstream>
#include <string>
#include "InfixParser.h"
#include "Operand.h"
#include "Tokenizer.h"
#include "Symboltable.h"

namespace psands_cisp430_a3
{
	class ExpressionEvaluator
	{
	private:
		std::string _expression;
		InfixParser * _infixParser;
		Tokenizer * _tokenizer;
		Symboltable * _symbolTable;
	public:
		ExpressionEvaluator();
		ExpressionEvaluator(std::string expression);
		~ExpressionEvaluator();
		void setExpression(std::string expression);
		double getExpressionResult();
		double getExpressionResult(std::string expression);
		void evaluateExpression();
		void evaluateExpression(std::string expression);
		std::ostream & displayExpression(std::ostream & ostream);
	};
}

#endif // PSANDS_CISP430_EXPRESSIONEVALUATOR_H