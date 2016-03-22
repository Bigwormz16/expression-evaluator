#ifndef PSANDS_CISP430_INFIXPARSER_H
#define PSANDS_CISP430_INFIXPARSER_H

#include "Queue.h"
#include "Token.h"

namespace psands_cisp430_a3
{
	class InfixParser
	{
	public:
		InfixParser();
		~InfixParser();
		psands_cisp430_a2::Queue<Token *> * getPostfixTokenQueue(psands_cisp430_a2::Queue<Token *> * infixTokenQueue);
	};
}

#endif // PSANDS_CISP430_INFIXPARSER_H