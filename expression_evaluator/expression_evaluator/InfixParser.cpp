#include "InfixParser.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

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
}

InfixParser::~InfixParser()
{
}

Queue<Token*>* InfixParser::getPostfixTokenQueue(Queue<Token*>* infixTokenQueue)
{
	Queue<Token *> * result = new Queue<Token*>(); // this is where the postfix expression will end up
	Stack<Token *> * s2 = new Stack<Token*>(); // this is the intermediate stack that stores operators

	while (!infixTokenQueue->isEmpty())
	{
		if (infixTokenQueue->peek()->getTokenType() == OPERAND)
		{
			this->infixNextStateS1(infixTokenQueue, result, s2);
		}
		else if ("=" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if (true == s2->isEmpty())
			{
				this->infixNextStateS2(infixTokenQueue, result, s2);
			}
			else
			{
				this->infixNextStateErr(infixTokenQueue, result, s2);
			}
		}
		else if ("+" == infixTokenQueue->peek()->getTokenSymbol() ||
			"-" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if (true == s2->isEmpty())
			{
				this->infixNextStateErr(infixTokenQueue, result, s2);
			}
			else if ("sin" == s2->peek()->getTokenSymbol() ||
				"cos" == s2->peek()->getTokenSymbol() ||
				"sqrt" == s2->peek()->getTokenSymbol() ||
				"abs" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateU1(infixTokenQueue, result, s2);
			}
			else if ("=" == s2->peek()->getTokenSymbol() ||
				"(" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateS2(infixTokenQueue, result, s2);
			}
			else if ("+" == s2->peek()->getTokenSymbol() ||
				"-" == s2->peek()->getTokenSymbol() ||
				"*" == s2->peek()->getTokenSymbol() ||
				"/" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateU1(infixTokenQueue, result, s2);
			}
		}
		else if ("*" == infixTokenQueue->peek()->getTokenSymbol() ||
			"/" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if (true == s2->isEmpty())
			{
				this->infixNextStateErr(infixTokenQueue, result, s2);
			}
			else if ("sin" == s2->peek()->getTokenSymbol() ||
				"cos" == s2->peek()->getTokenSymbol() ||
				"sqrt" == s2->peek()->getTokenSymbol() ||
				"abs" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateU1(infixTokenQueue, result, s2);
			}
			else if ("=" == s2->peek()->getTokenSymbol() ||
				"(" == s2->peek()->getTokenSymbol() ||
				"+" == s2->peek()->getTokenSymbol() ||
				"-" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateS2(infixTokenQueue, result, s2);
			}
			else if ("*" == s2->peek()->getTokenSymbol() ||
				"/" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateU1(infixTokenQueue, result, s2);
			}
		}
		else if ("(" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if (true == s2->isEmpty())
			{
				this->infixNextStateErr(infixTokenQueue, result, s2);
			}
			else
			{
				this->infixNextStateS2(infixTokenQueue, result, s2);
			}
		}
		else if (")" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if (true == s2->isEmpty() ||
				"=" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateErr(infixTokenQueue, result, s2);
			}
			else
			{
				this->infixNextStateUC(infixTokenQueue, result, s2);
			}
		}
		else if ("sin" == infixTokenQueue->peek()->getTokenSymbol() ||
			"cos" == infixTokenQueue->peek()->getTokenSymbol() || 
			"sqrt" == infixTokenQueue->peek()->getTokenSymbol() || 
			"abs" == infixTokenQueue->peek()->getTokenSymbol())
		{
			if ("sin" == s2->peek()->getTokenSymbol() ||
				"cos" == s2->peek()->getTokenSymbol() ||
				"sqrt" == s2->peek()->getTokenSymbol() ||
				"abs" == s2->peek()->getTokenSymbol())
			{
				this->infixNextStateU1(infixTokenQueue, result, s2);
			}
			else
			{
				this->infixNextStateS2(infixTokenQueue, result, s2);
			}
		}
	}

	if (!s2->isEmpty())
	{
		this->infixNextStateU2(infixTokenQueue, result, s2);
	}
	
	return result;
}
