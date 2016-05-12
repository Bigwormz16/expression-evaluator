// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "Token.h"
#include "AbstractOperator.h"
#include "PolynomialTerm.h"

using namespace psands_cisp430_a3;

Token::Token()
{
	this->_tokenType = BADTOKEN;
	this->_tokenPriority = 0;
}

Token::Token(std::string tokenSymbol, unsigned int tokenPriority) : Token()
{
	this->_tokenSymbol = tokenSymbol;
	this->_tokenPriority = tokenPriority;
}

Token::Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority) : Token(tokenSymbol, tokenPriority)
{
	this->_tokenType = tokenType;
}

Token::Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority, PolynomialTerm * term)
	: Token(tokenSymbol, tokenType, tokenPriority)
{
	this->_term = term;
}

Token::Token(std::string tokenSymbol, TokenType tokenType, unsigned int tokenPriority, AbstractOperator * abstractOperator)
	: Token(tokenSymbol, tokenType, tokenPriority)
{
	this->_abstractOperator = abstractOperator;
}

Token::~Token()
{
}

unsigned int Token::getTokenPriority()
{
	return this->_tokenPriority;
}

std::string Token::getTokenSymbol()
{
	return this->_tokenSymbol;
}

TokenType Token::getTokenType()
{
	return this->_tokenType;
}

PolynomialTerm * Token::getPolynomialTerm()
{
	if (true == this->_term->isTermWrapper())
	{
		return this->_term->getInnerTerm();
	}
	return this->_term;
}

AbstractOperator * Token::getOperator()
{
	return this->_abstractOperator;
}
