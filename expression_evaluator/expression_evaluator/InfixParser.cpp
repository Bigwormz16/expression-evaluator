#include "InfixParser.h"
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

void psands_cisp430_a3::InfixParser::infixNextStateS1(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	output->enqueue(input->dequeue());
}

void psands_cisp430_a3::InfixParser::infixNextStateS2(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	operatorStack->push(input->dequeue());
}

void psands_cisp430_a3::InfixParser::infixNextStateErr(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	// error occurred
}

void psands_cisp430_a3::InfixParser::infixNextStateU1(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	output->enqueue(operatorStack->pop());
}

void psands_cisp430_a3::InfixParser::infixNextStateU2(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	while (!operatorStack->isEmpty())
	{
		// for now, do not worry about "=" operator in expressions
		if ("=" == operatorStack->peek()->getTokenSymbol())
		{
			operatorStack->pop();
		}
		else
		{
			output->enqueue(operatorStack->pop());
		}
	}
}

void psands_cisp430_a3::InfixParser::infixNextStateUC(psands_cisp430_a2::Queue<Token*>* input, psands_cisp430_a2::Queue<Token*>* output, psands_cisp430_a2::Stack<Token*>* operatorStack)
{
	while ("(" != operatorStack->peek()->getTokenSymbol())
	{
		output->enqueue(operatorStack->pop());
	}
	operatorStack->pop(); // discard the "("
	input->dequeue(); // discard the ")"
}

psands_cisp430_a3::InfixParser::InfixParser()
{
}

psands_cisp430_a3::InfixParser::~InfixParser()
{
}

Queue<Token*>* psands_cisp430_a3::InfixParser::getPostfixTokenQueue(Queue<Token*>* infixTokenQueue)
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
	}

	if (!s2->isEmpty())
	{
		this->infixNextStateU2(infixTokenQueue, result, s2);
	}
	
	return result;
}
