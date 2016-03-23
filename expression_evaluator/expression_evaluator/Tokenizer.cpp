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
	this->_equalsToken = new psands_cisp430_a3::Token("=", ASSIGNMENTOPERATOR);
	this->_additionToken = new psands_cisp430_a3::Token("+", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::add));
	this->_subtractionToken = new psands_cisp430_a3::Token("-", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::subtract));
	this->_multiplicationToken = new psands_cisp430_a3::Token("*", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::multiply));
	this->_divisionToken = new psands_cisp430_a3::Token("/", BINARYOPERATOR, new BinaryOperator(psands_cisp430_a3::divide));
	this->_sinToken = new psands_cisp430_a3::Token("sin", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sin));
	this->_cosToken = new psands_cisp430_a3::Token("cos", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::cos));
	this->_sqrtToken = new psands_cisp430_a3::Token("sqrt", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::sqrt));
	this->_absToken = new psands_cisp430_a3::Token("abs", UNARYOPERATOR, new UnaryOperator(psands_cisp430_a3::abs));

	// special tokens
	this->_openParenToken = new psands_cisp430_a3::Token("(", SPECIAL);
	this->_closeParenToken = new psands_cisp430_a3::Token(")", SPECIAL);
}

psands_cisp430_a3::Tokenizer::Tokenizer(Symboltable * symboltable) : Tokenizer()
{
	this->_symboltable = symboltable;
}

psands_cisp430_a3::Tokenizer::~Tokenizer()
{
	// do not delete symbotable as that is handled elsewhere
}

psands_cisp430_a2::Queue<psands_cisp430_a3::Token*>* psands_cisp430_a3::Tokenizer::getTokenQueue(std::string expression)
{
	psands_cisp430_a2::Queue<psands_cisp430_a3::Token *> * result = new psands_cisp430_a2::Queue<psands_cisp430_a3::Token *>();

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
