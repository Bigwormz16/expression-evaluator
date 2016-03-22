#include "ExpressionEvaluator.h"
#include "InfixParser.h"
#include "Queue.h"
#include "Token.h"
#include "Tokenizer.h"

psands_cisp430_a3::ExpressionEvaluator::ExpressionEvaluator()
{
	this->_infixParser = new InfixParser();
	this->_tokenizer = new Tokenizer();
}

psands_cisp430_a3::ExpressionEvaluator::ExpressionEvaluator(std::string expression) : ExpressionEvaluator()
{
	this->setExpression(expression);
}

psands_cisp430_a3::ExpressionEvaluator::~ExpressionEvaluator()
{
}

void psands_cisp430_a3::ExpressionEvaluator::setExpression(std::string expression)
{
	this->_expression = expression;
}

/*
	Convert the expression into a token queue (tokens will be in infix order)
	Convert the token queue into a different token queue (tokens will be in postfix order)
	Evaluate the postfix token queue.
*/
double psands_cisp430_a3::ExpressionEvaluator::getExpressionResult()
{
	psands_cisp430_a2::Queue<Token *> * infixTokenQueue = this->_tokenizer->getTokenQueue(this->_expression);
	psands_cisp430_a2::Queue<Token *> * postfixTokenQueue = this->_infixParser->getPostfixTokenQueue(infixTokenQueue);

	// evaluate the postfixTokenQueue

	return 0.0;
}

std::ostream & psands_cisp430_a3::ExpressionEvaluator::displayExpression(std::ostream & out)
{
	out << this->_expression << std::endl;
	return out;
}
