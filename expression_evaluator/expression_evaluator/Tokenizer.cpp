#include <cmath>
#include <regex>
#include <string>
#include "Tokenizer.h"
#include "BinaryOperator.h"
#include "List.h"
#include "Token.h"
#include "UnaryOperator.h"

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

void psands_cisp430_a3::Tokenizer::processOperand(std::string operand, psands_cisp430_a2::Queue<Token *> * tokenizedQueue)
{
	if (0 == operand.length()) return;

	if ("sin" == operand || "cos" == operand || "sqrt" == operand || "abs" == operand)
	{
		this->processOperator(operand, tokenizedQueue);
	}
	else if ("A" == operand)
	{
		tokenizedQueue->enqueue(this->_aToken);
	}
	else if ("B" == operand)
	{
		tokenizedQueue->enqueue(this->_bToken);
	}
	else if ("C" == operand)
	{
		tokenizedQueue->enqueue(this->_cToken);
	}
	else if ("D" == operand)
	{
		tokenizedQueue->enqueue(this->_dToken);
	}
	else
	{
		try
		{
			double doubleOperand = std::stod(operand);
			tokenizedQueue->enqueue(new Token(operand, OPERAND, new Operand(doubleOperand)));
		}
		catch(std::exception e)
		{
			tokenizedQueue->enqueue(new Token(operand));
		}
	}
}

void psands_cisp430_a3::Tokenizer::processOperator(std::string oprator, psands_cisp430_a2::Queue<Token *> * tokenizedQueue)
{
	if (0 == oprator.length()) return;

	if ("=" == oprator)
	{
		tokenizedQueue->enqueue(this->_equalsToken);
	}
	else if ("+" == oprator)
	{
		tokenizedQueue->enqueue(this->_additionToken);
	}
	else if ("-" == oprator)
	{
		tokenizedQueue->enqueue(this->_subtractionToken);
	}
	else if ("*" == oprator)
	{
		tokenizedQueue->enqueue(this->_multiplicationToken);
	}
	else if ("/" == oprator)
	{
		tokenizedQueue->enqueue(this->_divisionToken);
	}
	else if ("sin" == oprator)
	{
		tokenizedQueue->enqueue(this->_sinToken);
	}
	else if ("cos" == oprator)
	{
		tokenizedQueue->enqueue(this->_cosToken);
	}
	else if ("sqrt" == oprator)
	{
		tokenizedQueue->enqueue(this->_sqrtToken);
	}
	else if ("abs" == oprator)
	{
		tokenizedQueue->enqueue(this->_absToken);
	}
	else if ("(" == oprator)
	{
		tokenizedQueue->enqueue(this->_openParenToken);
	}
	else if (")" == oprator)
	{
		tokenizedQueue->enqueue(this->_closeParenToken);
	}
	else
	{
		tokenizedQueue->enqueue(new Token(oprator));
	}
}

psands_cisp430_a3::Tokenizer::Tokenizer()
{
	// Initialize the arithmetic operators that are supported by application
	_equalsToken = new psands_cisp430_a3::Token("=");
	_additionToken = new psands_cisp430_a3::Token("+", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::add));
	_subtractionToken = new psands_cisp430_a3::Token("-", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::subtract));
	_multiplicationToken = new psands_cisp430_a3::Token("*", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::multiply));
	_divisionToken = new psands_cisp430_a3::Token("/", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::divide));
	_sinToken = new psands_cisp430_a3::Token("sin", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sin));
	_cosToken = new psands_cisp430_a3::Token("cos", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::cos));
	_sqrtToken = new psands_cisp430_a3::Token("sqrt", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sqrt));
	_absToken = new psands_cisp430_a3::Token("abs", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::abs));

	// special tokens
	_openParenToken = new psands_cisp430_a3::Token("(", SPECIAL);
	_closeParenToken = new psands_cisp430_a3::Token(")", SPECIAL);

	// Initialize operand tokens
	_aToken = new psands_cisp430_a3::Token("A", OPERAND, new Operand(5));
	_bToken = new psands_cisp430_a3::Token("B", OPERAND, new Operand(10));
	_cToken = new psands_cisp430_a3::Token("C", OPERAND, new Operand(-1));
	_dToken = new psands_cisp430_a3::Token("D", OPERAND, new Operand(2));
}

psands_cisp430_a3::Tokenizer::~Tokenizer()
{
}

psands_cisp430_a2::Queue<psands_cisp430_a3::Token*>* psands_cisp430_a3::Tokenizer::getTokenQueue(std::string expression)
{
	psands_cisp430_a2::Queue<psands_cisp430_a3::Token *> * result = new psands_cisp430_a2::Queue<psands_cisp430_a3::Token *>();

	std::regex operand("[a-zA-Z0-9]");
	std::regex oprator("[\+\-/\\*=()]");

	std::string nextOperand = "";
	std::string nextOperator = "";

	for (int i = 0; i < expression.length(); i++)
	{
		std::string currentCharacter = expression.substr(i, 1);

		if (std::regex_match(currentCharacter, operand))
		{
			nextOperand += currentCharacter;
			processOperator(nextOperator, result);
			nextOperator = "";
		}
		else if (std::regex_match(currentCharacter, oprator))
		{
			nextOperator = currentCharacter;
			processOperand(nextOperand, result);
			processOperator(nextOperator, result);
			nextOperand = "";
			nextOperator = "";
		}
	}

	// process final operand/operator
	processOperand(nextOperand, result);
	processOperator(nextOperator, result);

	return result;
}
