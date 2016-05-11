// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include <stdexcept> // invalid_argument exception
#include <string>
#include "ExpressionEvaluator.h"
#include "InfixParser.h"
#include "List.h"
#include "Operand.h"
#include "Queue.h"
#include "Token.h"
#include "Tokenizer.h"
#include "Variable.h"

using namespace std;
using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

ExpressionEvaluator::ExpressionEvaluator()
{
	this->_infixParser = new InfixParser();
	this->_symbolTable = new Symboltable(30, 3, 10);
	this->_tokenizer = new Tokenizer(this->_symbolTable);
}

ExpressionEvaluator::ExpressionEvaluator(string expression) : ExpressionEvaluator()
{
	this->setExpression(expression);
}

ExpressionEvaluator::~ExpressionEvaluator()
{
	delete this->_infixParser;
	delete this->_symbolTable;
	delete this->_tokenizer;
}

void ExpressionEvaluator::setExpression(string expression)
{
	this->_expression = expression;
}

std::string ExpressionEvaluator::getExpressionResult()
{
	return this->getExpressionResult(this->_expression);
}

/*
	Convert the expression into a token queue (tokens will be in infix order)
	Convert the token queue into a different token queue (tokens will be in postfix order)
	Evaluate the postfix token queue.
		evaluation algorithm as described in class:
		operands are added to an evaluation stack,
		when operators are encountered, a number of operands (specified by the type of operator) are passed to the operators operation method
		the result of the operation method is added to the evaluation stack
		a well-formed postfix expression should result in a single value remaining in the evaluation stack, which is the result of the expression.
*/
std::string ExpressionEvaluator::getExpressionResult(string expression)
{
	Queue<Token *> * infixTokenQueue = this->_tokenizer->getTokenQueue(expression);
	Queue<Token *> * postfixTokenQueue = this->_infixParser->getPostfixTokenQueue(infixTokenQueue);

	if (true == this->_infixParser->isError())
	{
		throw invalid_argument("Invalid expression format.");
	}

	// evaluate the postfixTokenQueue
	Stack<PolynomialTerm *> * evaluationStack = new Stack<PolynomialTerm *>();

	List<Operand *> * operandsToEvaluate = new List<Operand *>();

	Polynomial * result = new Polynomial();

	bool isFirstOpr = false;
	bool isSecondOpr = false;

	while (!postfixTokenQueue->isEmpty())
	{
		Token * currentToken = postfixTokenQueue->dequeue();
		TokenType currentTokenType = currentToken->getTokenType();

		if (TokenType::POLYNOMIALTERM == currentTokenType)
		{
			PolynomialTerm * term = currentToken->getPolynomialTerm();
			evaluationStack->push(term);

			if (false == isSecondOpr && true == isFirstOpr)
			{
				isSecondOpr = true;
				result->add(term);
				evaluationStack->pop();
			}
			if (false == isFirstOpr)
			{
				isFirstOpr = true;
			}
		}
		else if (UNARYOPERATOR == currentTokenType)
		{
			// unary operators need one operand
			//operandsToEvaluate->add(evaluationStack->pop());
		}
		else if (BINARYOPERATOR == currentTokenType)
		{
			// binary operators get two operands
			//operandsToEvaluate->add(evaluationStack->pop());
			//operandsToEvaluate->add(evaluationStack->pop());
		}
		else if (ASSIGNMENTOPERATOR == currentTokenType)
		{
			PolynomialTerm * assignmentVar = evaluationStack->pop();

			assignmentVar->getVarTerm()->setValue(result);
		}

		if (UNARYOPERATOR == currentTokenType ||
			BINARYOPERATOR == currentTokenType)
		{
			if ("+" == currentToken->getTokenSymbol())
			{
				result->add(evaluationStack->pop());
			}
			else if ("-" == currentToken->getTokenSymbol())
			{
				result->subtract(evaluationStack->pop());
			}
			else if ("*" == currentToken->getTokenSymbol())
			{
				result->multiply(evaluationStack->pop());
			}
		}
	}

	// clean up allocations
	delete infixTokenQueue;
	delete postfixTokenQueue;
	delete operandsToEvaluate;

	return result->toString();
}

void ExpressionEvaluator::evaluateExpression()
{
	this->evaluateExpression(this->_expression);
}

void psands_cisp430_a3::ExpressionEvaluator::evaluateExpression(std::string expression)
{
	this->getExpressionResult(expression);
}

ostream & ExpressionEvaluator::displayExpression(ostream & out)
{
	out << this->_expression << endl;
	return out;
}
