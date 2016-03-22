#ifndef PSANDS_CISP430_TOKEN_H
#define PSANDS_CISP430_TOKEN_H

#include <string>
#include "AbstractOperator.h"
#include "Operand.h"

namespace psands_cisp430_a3
{
	enum TokenType
	{
		OPERAND,
		UNARYOPERATOR,
		BINARYOPERATOR,
		SPECIAL,
		BADTOKEN
	};

	class Token
	{
	private:
		std::string _tokenSymbol;
		TokenType _tokenType;
		Operand * _operand;
		AbstractOperator * _abstractOperator;
	public:
		Token();
		Token(std::string tokenSymbol);
		Token(std::string tokenSymbol, TokenType tokenType);
		Token(std::string tokenSymbol, TokenType tokenType, Operand * operand);
		Token(std::string tokenSymbol, TokenType tokenType, AbstractOperator * abstractOperator);
		~Token();
		TokenType getTokenType();
		Operand * getOperand();
		AbstractOperator * getOperator();
	};
}

#endif // PSANDS_CISP430_TOKEN_H