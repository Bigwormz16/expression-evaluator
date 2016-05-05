// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "InfixParser.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"
#include "PolynomialTerm.h"

using namespace std;
using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

void InfixParser::infixNextStateS1(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	output->push(input->dequeue());
}

void InfixParser::infixNextStateS2(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	operatorStack->push(input->dequeue());
}

void InfixParser::infixNextStateErr(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	this->_isError = true;
}

void InfixParser::infixNextStateU1(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	output->push(operatorStack->pop());
}

void InfixParser::infixNextStateU2(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	while (!operatorStack->isEmpty())
	{
		output->push(operatorStack->pop());
	}
}

void InfixParser::infixNextStateUC(Queue<Token*>* input, Stack<Token*>* output, Stack<Token*>* operatorStack)
{
	while ("(" != operatorStack->peek()->getTokenSymbol())
	{
		output->push(operatorStack->pop());
	}
	operatorStack->pop(); // discard the "("
	input->dequeue(); // discard the ")"
}

psands_cisp430_a2::Queue<Token*>* psands_cisp430_a3::InfixParser::getPolynomialPostfixTokenQueue(psands_cisp430_a2::Stack<Token*> * postfixTokenQueue)
{
	Queue<Token *> * result = new Queue<Token *>();

	Token * previousToken = nullptr;
	bool isPolynomialTerm = false;
	bool hasCoefficient = false;
	bool hasSetExponent = false;
	bool hasSetToken = false;
	PolynomialTerm * term = nullptr;

	while (false == postfixTokenQueue->isEmpty())
	{
		Token * currentToken = postfixTokenQueue->pop();

		if (true == isPolynomialTerm)
		{
			if (false == hasSetExponent)
			{
				term->setExponent(currentToken->getOperand()->getValue());
				hasSetExponent = true;
			}
			else if (false == hasSetToken)
			{
				term->setToken(currentToken);
				hasSetToken = true;
			}
			else if(true == hasCoefficient)
			{
				term->setCoefficient(currentToken->getOperand()->getValue());

				isPolynomialTerm = false;
				hasCoefficient = false;
				hasSetExponent = false;
				hasSetToken = false;
			}
			else
			{
				term->setCoefficient(1);
				isPolynomialTerm = false;
				hasCoefficient = false;
				hasSetExponent = false;
				hasSetToken = false;
			}

		}

		if ("^" == currentToken->getTokenSymbol())
		{
			term = new PolynomialTerm();
			isPolynomialTerm = true;
			if ("*" == previousToken->getTokenSymbol())
			{
				hasCoefficient = true;
			}
		}

		previousToken = currentToken;
	}

	return result;
}

InfixParser::InfixParser()
{
	this->_isError = false;

	// operands
	this->_parsetable[0][0] = S1; this->_parsetable[0][1] = S1; this->_parsetable[0][2] = S1;
		this->_parsetable[0][3] = S1; this->_parsetable[0][4] = S1; this->_parsetable[0][5] = S1;
		this->_parsetable[0][6] = S1; this->_parsetable[0][7] = S1;
	// =
	this->_parsetable[1][0] = S2; this->_parsetable[1][1] = ERR; this->_parsetable[1][2] = ERR;
		this->_parsetable[1][3] = ERR; this->_parsetable[1][4] = ERR; this->_parsetable[1][5] = ERR;
		this->_parsetable[1][6] = ERR; this->_parsetable[1][7] = ERR;
	// +-
	this->_parsetable[2][0] = ERR; this->_parsetable[2][1] = S2; this->_parsetable[2][2] = U1;
		this->_parsetable[2][3] = U1; this->_parsetable[2][4] = U1; this->_parsetable[2][5] = U1;
		this->_parsetable[2][6] = U1; this->_parsetable[2][7] = S2;
	// */
	this->_parsetable[3][0] = ERR; this->_parsetable[3][1] = S2; this->_parsetable[3][2] = S2;
		this->_parsetable[3][3] = U1; this->_parsetable[3][4] = U1; this->_parsetable[3][5] = U1;
		this->_parsetable[3][6] = U1; this->_parsetable[3][7] = S2;
	// sin,cos,abs,sqrt
	this->_parsetable[4][0] = ERR; this->_parsetable[4][1] = S2; this->_parsetable[4][2] = S2;
		this->_parsetable[4][3] = S2; this->_parsetable[4][4] = U1; this->_parsetable[4][5] = U1;
		this->_parsetable[4][6] = U1; this->_parsetable[4][7] = S2;
	// neg
	this->_parsetable[5][0] = ERR; this->_parsetable[5][1] = S2; this->_parsetable[5][2] = S2;
		this->_parsetable[5][3] = S2; this->_parsetable[5][4] = S2; this->_parsetable[5][5] = U1;
		this->_parsetable[5][6] = U1; this->_parsetable[5][7] = S2;
	// exponent
	this->_parsetable[6][0] = ERR; this->_parsetable[6][1] = S2; this->_parsetable[6][2] = S2;
		this->_parsetable[6][3] = S2; this->_parsetable[6][4] = S2; this->_parsetable[6][5] = S2;
		this->_parsetable[6][6] = U1; this->_parsetable[6][7] = S2;
	// (
	this->_parsetable[7][0] = ERR; this->_parsetable[7][1] = S2; this->_parsetable[7][2] = S2;
		this->_parsetable[7][3] = S2; this->_parsetable[7][4] = S2; this->_parsetable[7][5] = S2;
		this->_parsetable[7][6] = S2; this->_parsetable[7][7] = S2;
	// )
	this->_parsetable[8][0] = ERR; this->_parsetable[8][1] = UC; this->_parsetable[8][2] = UC;
		this->_parsetable[8][3] = UC; this->_parsetable[8][4] = UC; this->_parsetable[8][5] = UC;
		this->_parsetable[8][6] = UC; this->_parsetable[8][7] = UC;

}

InfixParser::~InfixParser()
{
}

// store the completed postfix expression in a queue,
// store the intermediate operators (for priority) in a stack
// using the logic behind the NextState Pushdown Transducer, process each infix token in order
	// logic exists in an array, which mirrors nextstate pushdown transducer, which determines next action to take
Queue<Token*>* InfixParser::getPostfixTokenQueue(Queue<Token*>* infixTokenQueue)
{
	this->_isError = false;

	Stack<Token *> * postfixExpr = new Stack<Token*>(); // this is where the postfix expression will end up
	Stack<Token *> * s2 = new Stack<Token*>(); // this is the intermediate stack that stores operators

	while (!infixTokenQueue->isEmpty() && false == this->_isError)
	{
		unsigned int nextTokenPriority = infixTokenQueue->peek()->getTokenPriority();
		unsigned int s2TopTokenPriority = 0;
		if (!s2->isEmpty())
		{
			s2TopTokenPriority = s2->peek()->getTokenPriority();
		}

		ParseAction infixParseAction = this->_parsetable[nextTokenPriority][s2TopTokenPriority];

		switch (infixParseAction)
		{
		case S1:
			this->infixNextStateS1(infixTokenQueue, postfixExpr, s2);
			break;
		case S2:
			this->infixNextStateS2(infixTokenQueue, postfixExpr, s2);
			break;
		case U1:
			this->infixNextStateU1(infixTokenQueue, postfixExpr, s2);
			break;
		case U2:
			this->infixNextStateU2(infixTokenQueue, postfixExpr, s2);
			break;
		case UC:
			this->infixNextStateUC(infixTokenQueue, postfixExpr, s2);
			break;
		case ERR:
			this->infixNextStateErr(infixTokenQueue, postfixExpr, s2);
			break;
		}
	}

	if (!s2->isEmpty())
	{
		this->infixNextStateU2(infixTokenQueue, postfixExpr, s2);
	}

	Queue<Token *> * result = this->getPolynomialPostfixTokenQueue(postfixExpr);
	
	return result;
}

bool psands_cisp430_a3::InfixParser::isError()
{
	return this->_isError;
}
