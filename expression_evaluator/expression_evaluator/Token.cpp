#include "Token.h"
#include "AbstractOperator.h"
#include "Operand.h"

psands_cisp430_a3::Token::Token()
{
}

psands_cisp430_a3::Token::Token(std::string tokenSymbol, TokenType tokenType, Operand * operand)
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenType = tokenType;
	this->_operand = operand;
}

psands_cisp430_a3::Token::Token(std::string tokenSymbol, TokenType tokenType, AbstractOperator * abstractOperator)
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenType = tokenType;
	this->_abstractOperator = abstractOperator;
}

psands_cisp430_a3::Token::~Token()
{
}

psands_cisp430_a3::TokenType psands_cisp430_a3::Token::getTokenType()
{
	return this->_tokenType;
}

psands_cisp430_a3::Operand * psands_cisp430_a3::Token::getOperand()
{
	return this->_operand;
}

psands_cisp430_a3::AbstractOperator * psands_cisp430_a3::Token::getOperator()
{
	return this->_abstractOperator;
}
