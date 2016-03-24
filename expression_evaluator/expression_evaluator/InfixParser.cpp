// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include "InfixParser.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

using namespace std;
using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

void InfixParser::infixNextStateS1(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	output->enqueue(input->dequeue());
}

void InfixParser::infixNextStateS2(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	operatorStack->push(input->dequeue());
}

void InfixParser::infixNextStateErr(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	// error occurred - how to handle?
}

void InfixParser::infixNextStateU1(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	output->enqueue(operatorStack->pop());
}

void InfixParser::infixNextStateU2(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	while (!operatorStack->isEmpty())
	{
		output->enqueue(operatorStack->pop());
	}
}

void InfixParser::infixNextStateUC(Queue<Token*>* input, Queue<Token*>* output, Stack<Token*>* operatorStack)
{
	while ("(" != operatorStack->peek()->getTokenSymbol())
	{
		output->enqueue(operatorStack->pop());
	}
	operatorStack->pop(); // discard the "("
	input->dequeue(); // discard the ")"
}

InfixParser::InfixParser()
{
	// operands
	this->_parsetable[0][0] = S1; this->_parsetable[0][1] = S1; this->_parsetable[0][2] = S1;
		this->_parsetable[0][3] = S1; this->_parsetable[0][4] = S1; this->_parsetable[0][5] = S1;
	// =
	this->_parsetable[1][0] = S2; this->_parsetable[1][1] = ERR; this->_parsetable[1][2] = ERR;
		this->_parsetable[1][3] = ERR; this->_parsetable[1][4] = ERR; this->_parsetable[1][5] = ERR;
	// +-
	this->_parsetable[2][0] = ERR; this->_parsetable[2][1] = S2; this->_parsetable[2][2] = U1;
		this->_parsetable[2][3] = U1; this->_parsetable[2][4] = U1; this->_parsetable[2][5] = S2;
	// */
	this->_parsetable[3][0] = ERR; this->_parsetable[3][1] = S2; this->_parsetable[3][2] = S2;
		this->_parsetable[3][3] = U1; this->_parsetable[3][4] = U1; this->_parsetable[3][5] = S2;
	// sin,cos,abs,sqrt
	this->_parsetable[4][0] = ERR; this->_parsetable[4][1] = S2; this->_parsetable[4][2] = S2;
		this->_parsetable[4][3] = S2; this->_parsetable[4][4] = U1; this->_parsetable[4][5] = S2;
	// (
	this->_parsetable[5][0] = ERR; this->_parsetable[5][1] = S2; this->_parsetable[5][2] = S2;
		this->_parsetable[5][3] = S2; this->_parsetable[5][4] = S2; this->_parsetable[5][5] = S2;
	// )
	this->_parsetable[6][0] = ERR; this->_parsetable[6][1] = UC; this->_parsetable[6][2] = UC;
		this->_parsetable[6][3] = UC; this->_parsetable[6][4] = UC; this->_parsetable[6][5] = UC;

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
	Queue<Token *> * result = new Queue<Token*>(); // this is where the postfix expression will end up
	Stack<Token *> * s2 = new Stack<Token*>(); // this is the intermediate stack that stores operators

	while (!infixTokenQueue->isEmpty())
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
			this->infixNextStateS1(infixTokenQueue, result, s2);
			break;
		case S2:
			this->infixNextStateS2(infixTokenQueue, result, s2);
			break;
		case U1:
			this->infixNextStateU1(infixTokenQueue, result, s2);
			break;
		case U2:
			this->infixNextStateU2(infixTokenQueue, result, s2);
			break;
		case UC:
			this->infixNextStateUC(infixTokenQueue, result, s2);
			break;
		case ERR:
			this->infixNextStateErr(infixTokenQueue, result, s2);
			break;
		}
	}

	if (!s2->isEmpty())
	{
		this->infixNextStateU2(infixTokenQueue, result, s2);
	}
	
	return result;
}
