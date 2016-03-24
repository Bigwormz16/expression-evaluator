#include "Token.h"
#include "AbstractOperator.h"
#include "Operand.h"

using namespace psands_cisp430_a3;

Token::Token()
{
}

Token::Token(std::string tokenSymbol)
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenType = BADTOKEN;
}

Token::Token(std::string tokenSymbol, TokenType tokenType) : Token(tokenSymbol)
{
	this->_tokenType = tokenType;
}

Token::Token(std::string tokenSymbol, TokenType tokenType, Operand * operand)
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenType = tokenType;
	this->_operand = operand;
}

std::string Token::getTokenSymbol()
{
	return this->_tokenSymbol;
}

Token::Token(std::string tokenSymbol, TokenType tokenType, AbstractOperator * abstractOperator)
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenType = tokenType;
	this->_abstractOperator = abstractOperator;
}

Token::~Token()
{
}

TokenType Token::getTokenType()
{
	return this->_tokenType;
}

Operand * Token::getOperand()
{
	return this->_operand;
}

AbstractOperator * Token::getOperator()
{
	return this->_abstractOperator;
}
