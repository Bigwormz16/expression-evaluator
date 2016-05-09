// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// Represents an individual component of an expression, either operand or operator.
//		Stores the type of token it is as well as the priority it runs at

#ifndef PSANDS_CISP430_TOKEN_H
#define PSANDS_CISP430_TOKEN_H

#include <string>
#include "AbstractOperator.h"
#include "Operand.h"
#include "PolynomialTerm.h"

namespace psands_cisp430_a3
{
	enum TokenType
	{
		OPERAND,
		VARIABLE,
		POLYNOMIALTERM,
		UNARYOPERATOR,
		BINARYOPERATOR,
		ASSIGNMENTOPERATOR,
		SPECIAL,
		BADTOKEN
	};

	class Token
	{
	private:
		unsigned int _tokenPriority;
		std::string _tokenSymbol;
		TokenType _tokenType;
		Operand * _operand;
		AbstractOperator * _abstractOperator;
	public:
		Token();
		Token(std::string tokenSymbol, unsigned int tokenPriority);
		Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority);
		Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority, Operand * operand);
		Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority, AbstractOperator * abstractOperator);
		~Token();
		unsigned int getTokenPriority();
		std::string getTokenSymbol();
		TokenType getTokenType();
		Operand * getOperand();
		AbstractOperator * getOperator();
	};
}

#endif // PSANDS_CISP430_TOKEN_H