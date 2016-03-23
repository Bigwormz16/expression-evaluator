#ifndef PSANDS_CISP430_TOKENIZER_H
#define PSANDS_CISP430_TOKENIZER_H

#include <string>
#include "List.h"
#include "Queue.h"
#include "Token.h"

namespace psands_cisp430_a3
{
	class Tokenizer
	{
	private:
		Token * _equalsToken;
		Token * _additionToken, *_subtractionToken, *_multiplicationToken, *_divisionToken;
		Token * _openParenToken, *_closeParenToken;
		Token * _sinToken, *_cosToken, *_sqrtToken, *_absToken;
		Token * _aToken, *_bToken, *_cToken, *_dToken;
		void processOperand(std::string operand, psands_cisp430_a2::Queue<Token *> * tokenizedQueue);
		void processOperator(std::string oprator, psands_cisp430_a2::Queue<Token *> * tokenizedQueue);
	public:
		Tokenizer();
		~Tokenizer();
		psands_cisp430_a2::Queue<Token *> * getTokenQueue(std::string expression);
	};
}

#endif // PSANDS_CISP430_TOKENIZER_H
