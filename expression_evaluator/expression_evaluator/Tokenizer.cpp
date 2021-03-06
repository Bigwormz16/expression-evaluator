// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

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
	double negative(double p1) { return p1 * -1; }
}
// to this point the operand has been the combination of sequential characters fitting in a-z, A-Z, 0-9, and the . character
// first step is to determine if the combination of characters actually represents an operator: "sin", "cos", "sqrt", or "abs" for our purposes
// if it does, then process as operator
// otherwise, determine if the characters make up a numeric value, then
	// create a new operand token 
// if it is actually a collection of characters and numbers, then it is a variable
	// retrieve value from symboltable or create new entry if it does not exist
	// store this symboltable operand as a token
void Tokenizer::processOperand(std::string operand, bool isPrevTokenOperator, Queue<Token *> * tokenizedQueue)
{
	if (0 == operand.length()) return;

	if ("sin" == operand || "cos" == operand || "sqrt" == operand || "abs" == operand)
	{
		this->processOperator(operand, isPrevTokenOperator, tokenizedQueue);
	}
	else
	{
		try
		{
			double doubleOperand = std::stod(operand);
			tokenizedQueue->enqueue(new Token(operand, OPERAND, 0, new Operand(doubleOperand)));
		}
		catch(...)
		{
			Operand * oprnd = this->_symboltable->get(operand);
			if (nullptr == oprnd)
			{
				oprnd = new Operand(0.0);
				this->_symboltable->insert(operand, oprnd);
			}
			tokenizedQueue->enqueue(new Token(operand, OPERAND, 0, oprnd));
		}
	}
}

void Tokenizer::processOperator(std::string oprator, bool isPrevTokenOperator, Queue<Token *> * tokenizedQueue)
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
		// determining negative sign as "-" which is preceeded by another operator
		if (true == isPrevTokenOperator)
		{
			tokenizedQueue->enqueue(this->_negativeToken);
		}
		// determining subtraction sign as "-" which is preceeded by a non-operator (operand)
		else
		{
			tokenizedQueue->enqueue(this->_subtractionToken);
		}
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
}

Tokenizer::Tokenizer()
{
	// Initialize the arithmetic operators that are supported by application
	this->_equalsToken = new Token("=", ASSIGNMENTOPERATOR, 1);
	this->_additionToken = new Token("+", BINARYOPERATOR, 2, new BinaryOperator(add));
	this->_subtractionToken = new Token("-", BINARYOPERATOR, 2, new BinaryOperator(subtract));
	this->_multiplicationToken = new Token("*", BINARYOPERATOR, 3, new BinaryOperator(multiply));
	this->_divisionToken = new Token("/", BINARYOPERATOR, 3, new BinaryOperator(divide));
	this->_sinToken = new Token("sin", UNARYOPERATOR, 4, new UnaryOperator(sin));
	this->_cosToken = new Token("cos", UNARYOPERATOR, 4, new UnaryOperator(cos));
	this->_sqrtToken = new Token("sqrt", UNARYOPERATOR, 4, new UnaryOperator(sqrt));
	this->_absToken = new Token("abs", UNARYOPERATOR, 4, new UnaryOperator(abs));

	// adding support for negative sign, which is a unary operation converting the sign of a single operand
	// higher priority than other operations
	this->_negativeToken = new Token("neg", UNARYOPERATOR, 5, new UnaryOperator(negative));

	// special tokens
	this->_openParenToken = new Token("(", SPECIAL, 5);
	this->_closeParenToken = new Token(")", SPECIAL, 6);
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

// take the expression one character at a time,
	// if the current character matches a known operand pattern, then start building a concatenation of the operand symbol
	// if the current character matches a known operator pattern, then it should be a single character operator pattern
		// for each operator processed, process it immediately, as it should only be a single character
		// for each operand character processed, build on it until an operator is detected, only then process it
	// at the end, process any remaining operand or operator tokens
Queue<Token*>* Tokenizer::getTokenQueue(std::string expression)
{
	Queue<Token *> * result = new Queue<Token *>();

	std::regex operand("[a-zA-Z0-9\.]");
	std::regex oprator("[\+\-/\\*=()]");

	std::string nextOperand = "";
	std::string nextOperator = "";

	bool isPreviousTokenOperator = false;

	for (int i = 0; i < expression.length(); i++)
	{
		std::string currentCharacter = expression.substr(i, 1);

		if (std::regex_match(currentCharacter, operand))
		{
			nextOperand += currentCharacter;
			this->processOperator(nextOperator, isPreviousTokenOperator, result);
			nextOperator = "";

			isPreviousTokenOperator = false;
		}
		else if (std::regex_match(currentCharacter, oprator))
		{
			nextOperator = currentCharacter;
			this->processOperand(nextOperand, isPreviousTokenOperator, result);
			this->processOperator(nextOperator, isPreviousTokenOperator, result);
			nextOperand = "";
			nextOperator = "";

			isPreviousTokenOperator = true;
		}
	}

	// process final operand/operator
	this->processOperand(nextOperand, isPreviousTokenOperator, result);
	this->processOperator(nextOperator, isPreviousTokenOperator, result);

	return result;
}
