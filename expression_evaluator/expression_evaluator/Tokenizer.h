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
		psands_cisp430_a2::List<Token *> * _operandTokens;
	public:
		Tokenizer();
		~Tokenizer();
		psands_cisp430_a2::Queue<Token *> * getTokenQueue(std::string expression);
	};
}

#endif // PSANDS_CISP430_TOKENIZER_H
