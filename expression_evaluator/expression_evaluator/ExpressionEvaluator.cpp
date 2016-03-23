#include "ExpressionEvaluator.h"
#include "InfixParser.h"
#include "List.h"
#include "Operand.h"
#include "Queue.h"
#include "Token.h"
#include "Tokenizer.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

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
		evaluation algorithm as described in class:
		operands are added to an evaluation stack,
		when operators are encountered, a number of operands (specified by the type of operator) are passed to the operators operation method
		the result of the operation method is added to the evaluation stack
		a well-formed postfix expression should result in a single value remaining in the evaluation stack, which is the result of the expression.
*/
double psands_cisp430_a3::ExpressionEvaluator::getExpressionResult()
{
	psands_cisp430_a2::Queue<Token *> * infixTokenQueue = this->_tokenizer->getTokenQueue(this->_expression);
	psands_cisp430_a2::Queue<Token *> * postfixTokenQueue = this->_infixParser->getPostfixTokenQueue(infixTokenQueue);

	// evaluate the postfixTokenQueue
	Stack<double> * evaluationStack = new Stack<double>();

	// on first pass, do not evaluate expression (ignore "=" and first operand)
	postfixTokenQueue->dequeue(); // removing the first operand from evaluation

	List<double> * operandsToEvaluate = new List<double>();

	while (!postfixTokenQueue->isEmpty())
	{
		TokenType currentTokenType = postfixTokenQueue->peek()->getTokenType();

		if (OPERAND == currentTokenType)
		{
			evaluationStack->push(postfixTokenQueue->dequeue()->getOperand()->getValue());
		}
		else if (UNARYOPERATOR == currentTokenType)
		{
			// unary operators need one operand
			operandsToEvaluate->add(evaluationStack->pop()); 
		}
		else if (BINARYOPERATOR == currentTokenType)
		{
			// binary operators get two operands	
			operandsToEvaluate->add(evaluationStack->pop());
			operandsToEvaluate->add(evaluationStack->pop()); 		
		}

		if (UNARYOPERATOR == currentTokenType ||
			BINARYOPERATOR == currentTokenType)
		{
			double evaluatedResult = postfixTokenQueue->dequeue()->getOperator()->Evaluate(operandsToEvaluate);
			evaluationStack->push(evaluatedResult);

			// after evaluating operands, remove them from the list for the next operation
			operandsToEvaluate->removeAll();
		}
	}

	double result = evaluationStack->pop();

	// clean up allocations
	delete infixTokenQueue;
	delete postfixTokenQueue;
	delete operandsToEvaluate;
	
	return evaluationStack->pop();
}

std::ostream & psands_cisp430_a3::ExpressionEvaluator::displayExpression(std::ostream & out)
{
	out << this->_expression << std::endl;
	return out;
}
