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
*/
double psands_cisp430_a3::ExpressionEvaluator::getExpressionResult()
{
	psands_cisp430_a2::Queue<Token *> * infixTokenQueue = this->_tokenizer->getTokenQueue(this->_expression);
	psands_cisp430_a2::Queue<Token *> * postfixTokenQueue = this->_infixParser->getPostfixTokenQueue(infixTokenQueue);

	// evaluate the postfixTokenQueue
	Stack<double> * evaluationStack = new Stack<double>();

	// on first pass, do not evaluate expression (ignore "=" and first operand)
	postfixTokenQueue->dequeue(); // removing the first operand from evaluation

	while (!postfixTokenQueue->isEmpty())
	{
		if (OPERAND == postfixTokenQueue->peek()->getTokenType())
		{
			evaluationStack->push(postfixTokenQueue->dequeue()->getOperand()->getValue());
		}
		else if (UNARYOPERATOR == postfixTokenQueue->peek()->getTokenType())
		{
			List<double> * evaluations = new List<double>();
			evaluations->add(evaluationStack->pop());

			double evaluatedResult = postfixTokenQueue->dequeue()->getOperator()->Evaluate(evaluations);

			evaluationStack->push(evaluatedResult);
		}
		else if (BINARYOPERATOR == postfixTokenQueue->peek()->getTokenType())
		{
			List<double> * evaluations = new List<double>();
			evaluations->add(evaluationStack->pop());
			evaluations->add(evaluationStack->pop());

			double evaluatedResult = postfixTokenQueue->dequeue()->getOperator()->Evaluate(evaluations);

			evaluationStack->push(evaluatedResult);
		}
	}
	

	return evaluationStack->pop();
}

std::ostream & psands_cisp430_a3::ExpressionEvaluator::displayExpression(std::ostream & out)
{
	out << this->_expression << std::endl;
	return out;
}
