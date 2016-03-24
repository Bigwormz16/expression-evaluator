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