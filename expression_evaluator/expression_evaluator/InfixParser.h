// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#ifndef PSANDS_CISP430_INFIXPARSER_H
#define PSANDS_CISP430_INFIXPARSER_H

#include <string>
#include "Queue.h"
#include "Stack.h"
#include "Token.h"

namespace psands_cisp430_a3
{
	enum ParseAction
	{
		S1,
		S2,
		U1,
		U2,
		UC,
		ERR
	};

	class InfixParser
	{
	private:
		ParseAction _parsetable[7][6];
		void infixNextStateS1(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		void infixNextStateS2(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		void infixNextStateErr(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		void infixNextStateU1(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		void infixNextStateU2(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		void infixNextStateUC(psands_cisp430_a2::Queue<Token *> * input, psands_cisp430_a2::Queue<Token *> * output, psands_cisp430_a2::Stack<Token *> * operatorStack);
		
	public:
		InfixParser();
		~InfixParser();
		psands_cisp430_a2::Queue<Token *> * getPostfixTokenQueue(psands_cisp430_a2::Queue<Token *> * infixTokenQueue);
	};
}

#endif // PSANDS_CISP430_INFIXPARSER_H