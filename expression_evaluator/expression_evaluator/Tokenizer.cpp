#include <cmath>
#include <regex>
#include "Tokenizer.h"
#include "BinaryOperator.h"
#include "List.h"
#include "Token.h"
#include "UnaryOperator.h"

using namespace psands_cisp430_a2;

namespace psands_cisp430_a3 {
	double add(double p1, double p2) { return p1 + p2; }
	double subtract(double p1, double p2) { return p1 - p2; }
	double multiply(double p1, double p2) { return p1 * p2; }
	double divide(double p1, double p2) { return p1 / p2; }
	double sin(double p1) { return std::sin(p1); }
	double cos(double p1) { return std::cos(p1); }
	double sqrt(double p1) { return std::sqrt(p1); }
	double abs(double p1) { return std::abs(p1); }
}

psands_cisp430_a3::Tokenizer::Tokenizer()
{
	// Initialize the arithmetic operators that are supported by application
	_operandTokens = new List<Token *>();
	_operandTokens->add(new Token("+", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::add)));
	_operandTokens->add(new Token("-", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::subtract)));
	_operandTokens->add(new Token("*", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::multiply)));
	_operandTokens->add(new Token("/", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::divide)));
	_operandTokens->add(new Token("sin", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sin)));
	_operandTokens->add(new Token("cos", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::cos)));
	_operandTokens->add(new Token("sqrt", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sqrt)));
	_operandTokens->add(new Token("abs", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::abs)));
}

psands_cisp430_a3::Tokenizer::~Tokenizer()
{
}

psands_cisp430_a2::Queue<psands_cisp430_a3::Token*>* psands_cisp430_a3::Tokenizer::getTokenQueue(std::string expression)
{
	psands_cisp430_a2::Queue<Token *> * result = new psands_cisp430_a2::Queue<Token *>();

	std::regex operand("[a-zA-Z0-9]");

	for (int i = 0; i < expression.length(); i++)
	{
		if (std::regex_match(expression.substr(i, 1), operand))
		{

		}
	}
}
