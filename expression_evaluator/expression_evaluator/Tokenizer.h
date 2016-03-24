// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

// Converts a string expression into a tokenized expression in queue form.

#ifndef PSANDS_CISP430_TOKENIZER_H
#define PSANDS_CISP430_TOKENIZER_H

#include <string>
#include "List.h"
#include "Queue.h"
#include "Symboltable.h"
#include "Token.h"

namespace psands_cisp430_a3
{
	class Tokenizer
	{
	private:
		Symboltable * _symboltable;
		Token * _equalsToken;
		Token * _additionToken, *_subtractionToken, *_multiplicationToken, *_divisionToken;
		Token * _openParenToken, *_closeParenToken;
		Token * _sinToken, *_cosToken, *_sqrtToken, *_absToken;
		void processOperand(std::string operand, psands_cisp430_a2::Queue<Token *> * tokenizedQueue);
		void processOperator(std::string oprator, psands_cisp430_a2::Queue<Token *> * tokenizedQueue);
	public:
		Tokenizer();
		Tokenizer(Symboltable * symboltable);
		~Tokenizer();
		psands_cisp430_a2::Queue<Token *> * getTokenQueue(std::string expression);
	};
}

#endif // PSANDS_CISP430_TOKENIZER_H
