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
	this->_parsetable[0][0] = "s1"; this->_parsetable[0][1] = "s1"; this->_parsetable[0][2] = "s1";
		this->_parsetable[0][3] = "s1"; this->_parsetable[0][4] = "s1"; this->_parsetable[0][5] = "s1";
		this->_parsetable[1][0] = "s2"; this->_parsetable[1][1] = "err"; this->_parsetable[1][2] = "err";
		this->_parsetable[1][3] = "err"; this->_parsetable[1][4] = "err"; this->_parsetable[1][5] = "err";
		this->_parsetable[2][0] = "err"; this->_parsetable[2][1] = "s2"; this->_parsetable[2][2] = "u1";
		this->_parsetable[2][3] = "u1"; this->_parsetable[2][4] = "u1"; this->_parsetable[2][5] = "s2";
		this->_parsetable[3][0] = "err"; this->_parsetable[3][1] = "s2"; this->_parsetable[3][2] = "s2";
		this->_parsetable[3][3] = "u1"; this->_parsetable[3][4] = "u1"; this->_parsetable[3][5] = "s2";
		this->_parsetable[4][0] = "err"; this->_parsetable[4][1] = "s2"; this->_parsetable[4][2] = "s2";
		this->_parsetable[4][3] = "s2"; this->_parsetable[4][4] = "u1"; this->_parsetable[4][5] = "s2";
		this->_parsetable[5][0] = "err"; this->_parsetable[5][1] = "s2"; this->_parsetable[5][2] = "s2";
		this->_parsetable[5][3] = "s2"; this->_parsetable[5][4] = "s2"; this->_parsetable[5][5] = "s2";
		this->_parsetable[6][0] = "err"; this->_parsetable[6][1] = "uc"; this->_parsetable[6][2] = "uc";
		this->_parsetable[6][3] = "uc"; this->_parsetable[6][4] = "uc"; this->_parsetable[6][5] = "uc";

}

InfixParser::~InfixParser()
{
}

// store the completed postfix expression in a queue,
// store the intermediate operators (for priority) in a stack
// using the logic behind the NextState Pushdown Transducer, process each infix token in order
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

		string infixAction = this->_parsetable[nextTokenPriority][s2TopTokenPriority];

		if ("s1" == infixAction)
		{
			this->infixNextStateS1(infixTokenQueue, result, s2);
		}
		else if ("s2" == infixAction)
		{
			this->infixNextStateS2(infixTokenQueue, result, s2);
		}
		else if ("err" == infixAction)
		{
			this->infixNextStateErr(infixTokenQueue, result, s2);
		}
		else if ("u1" == infixAction)
		{
			this->infixNextStateU1(infixTokenQueue, result, s2);
		}
		else if ("u2" == infixAction)
		{
			this->infixNextStateU2(infixTokenQueue, result, s2);
		}
		else if ("uc" == infixAction)
		{
			this->infixNextStateUC(infixTokenQueue, result, s2);
		}
	}

	if (!s2->isEmpty())
	{
		this->infixNextStateU2(infixTokenQueue, result, s2);
	}
	
	return result;
}
