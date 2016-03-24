#include <cmath>
#include <regex>
#include <string>
#include "Tokenizer.h"
#include "BinaryOperator.h"
#include "List.h"
#include "Token.h"
#include "UnaryOperator.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

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

void Tokenizer::processOperand(std::string operand, Queue<Token *> * tokenizedQueue)
{
	if (0 == operand.length()) return;

	if ("sin" == operand || "cos" == operand || "sqrt" == operand || "abs" == operand)
	{
		this->processOperator(operand, tokenizedQueue);
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
			Operand * oprnd = this->_symboltable->get(operand);
			if (nullptr == oprnd)
			{
				oprnd = new Operand(0.0);
				this->_symboltable->insert(operand, oprnd);
			}
			tokenizedQueue->enqueue(new Token(operand, OPERAND, oprnd));
		}
	}
}

void Tokenizer::processOperator(std::string oprator, Queue<Token *> * tokenizedQueue)
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

Tokenizer::Tokenizer()
{
	// Initialize the arithmetic operators that are supported by application
	this->_equalsToken = new Token("=", ASSIGNMENTOPERATOR);
	this->_additionToken = new Token("+", BINARYOPERATOR, new BinaryOperator(add));
	this->_subtractionToken = new Token("-", BINARYOPERATOR, new BinaryOperator(subtract));
	this->_multiplicationToken = new Token("*", BINARYOPERATOR, new BinaryOperator(multiply));
	this->_divisionToken = new Token("/", BINARYOPERATOR, new BinaryOperator(divide));
	this->_sinToken = new Token("sin", UNARYOPERATOR, new UnaryOperator(sin));
	this->_cosToken = new Token("cos", UNARYOPERATOR, new UnaryOperator(cos));
	this->_sqrtToken = new Token("sqrt", UNARYOPERATOR, new UnaryOperator(sqrt));
	this->_absToken = new Token("abs", UNARYOPERATOR, new UnaryOperator(abs));

	// special tokens
	this->_openParenToken = new Token("(", SPECIAL);
	this->_closeParenToken = new Token(")", SPECIAL);
}

Tokenizer::Tokenizer(Symboltable * symboltable) : Tokenizer()
{
	this->_symboltable = symboltable;
}

Tokenizer::~Tokenizer()
{
	// do not delete symbotable as that is handled elsewhere

	delete this->_equalsToken;
	delete this->_additionToken;
	delete this->_subtractionToken;
	delete this->_multiplicationToken;
	delete this->_divisionToken;
	delete this->_sinToken;
	delete this->_cosToken;
	delete this->_sqrtToken;
	delete this->_absToken;
	delete this->_openParenToken;
	delete this->_closeParenToken;
}

Queue<Token*>* Tokenizer::getTokenQueue(std::string expression)
{
	Queue<Token *> * result = new Queue<Token *>();

	std::regex operand("[a-zA-Z0-9\.]");
	std::regex oprator("[\+\-/\\*=()]");

	std::string nextOperand = "";
	std::string nextOperator = "";

	for (int i = 0; i < expression.length(); i++)
	{
		std::string currentCharacter = expression.substr(i, 1);

		if (std::regex_match(currentCharacter, operand))
		{
			nextOperand += currentCharacter;
			this->processOperator(nextOperator, result);
			nextOperator = "";
		}
		else if (std::regex_match(currentCharacter, oprator))
		{
			nextOperator = currentCharacter;
			this->processOperand(nextOperand, result);
			this->processOperator(nextOperator, result);
			nextOperand = "";
			nextOperator = "";
		}
	}

	// process final operand/operator
	this->processOperand(nextOperand, result);
	this->processOperator(nextOperator, result);

	return result;
}
