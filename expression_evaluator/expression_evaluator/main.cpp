// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

/*

Polynomial => an expression that may be made up of multiple polynomial terms

Polynomial Term => an expression in the form of c_a * v ^ c_b, where c_a and c_b are constants
					and v is a variable

Variable => a variable is a storage container for a Polynomial (keeping in mind that a polynomial may be evaluated)




*/


#include <iostream>
#include <string>
#include <stdexcept> // invalid_argument exception
#include "ExpressionEvaluator.h"
#include "Report.h"

using namespace std;
using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

string getReportHeader();
void generateExpressionReport(string fileName = "expression-report.txt");

int displayMainMenu();
void displayInteractiveExpressionEvaluator();
void displayReportGenerator();

/*
	Goal: Demonstrate expression evaluation and variable assignment by allowing interactive
		expression evaluation or generating report that evaluates expressions defined in
		assignment spec.

	Interactive Expression Evaluation
		Loop until "(Q)uit is selected"
		
			Allow user to enter a valid expression,
					i.e., "alpha = 5 * 10 + 3"
				Display evaluated result of expression,
					i.e., "53"
				Store evaluated result in variable (symbol),
					i.e., "alpha = 53"

			Allow user to enter a variable (symbol),
					i.e., "alpha"
				Display current value stored in variable (symbol),
					i.e., "53"

			Allow user to quit entering expressions and variables by
				entering "Q" or "q" to quit


	Generate report that fully demonstrates the expression evaluator by evaluating
		each expression defined in the assignment specification.

			assign initial values to variables:
				alpha = 5
				beta = 10
				gamma = -1
				delta = 2
			bonus: demonstrate assigning value to variable with alpha numeric name
				alpha1 = alpha + beta (15)

			assign alpha value of expression: alpha + beta / gamma * delta => 5 + 10 / -1 * 2 => 
				-15
			assign beta value of expression: 5 / 2.00 + alpha => 5 / 2.00 + -15 =>
				-12.5
			assign gamma value of expression: sin(alpha) + (gamma-delta) * 3 => -0.65029 + (-1-2) * 3 =>
				-9.65029
			assign delta value of expression: alpha - beta * gamma / delta => -15 - -12.5 * -9.65029 / 2 =>
				-75.314

	Allow user to quit the program by entering "Q" or "q" to quit
		
*/
int main(void)
{
	int userChoice = 0;
	while (-1 != userChoice)
	{
		userChoice = displayMainMenu();

		if (1 == userChoice)
		{
			displayInteractiveExpressionEvaluator();
		}
		else if (2 == userChoice)
		{
			displayReportGenerator();
		}

	}

	//generateExpressionReport("C:\\Users\\peter\\Documents\\rep\\expression-report.txt");

	return 0;
}

string getReportHeader()
{
	return "Peter Sands\nW1541805\nCISP 430 WED 6:30\nSpring 2016\nAssign 3\n";
}

void generateExpressionReport(string fileName)
{
	Report expressionReport;
	expressionReport.setReportHeader(getReportHeader());
	expressionReport.setReportTitle("\t\t\tExpression Evaluator Report\n\n");

	expressionReport.addContent("Goal: To demonstrate expression evaluation and assignment of evaluation to variables.\n");
	expressionReport.addContent("Demonstration will consist of evaluating expressions provided in assignment.\n\n");

	ExpressionEvaluator * evaluator = new ExpressionEvaluator();
	expressionReport.addContent("Assigning value 5 to variable alpha with expression: \n\t\"alpha = 5\"\n");
	evaluator->evaluateExpression("alpha = 5");
	expressionReport.addContent("Assigning value 10 to variable beta with expression: \n\t\"beta = 10\"\n");
	evaluator->evaluateExpression("beta = 10");
	expressionReport.addContent("Assigning sum of alpha and beta to variable alpha1 with expression: \n\t\"alpha1 = alpha + beta\"\n");
	evaluator->evaluateExpression("alpha1 = alpha + beta");
	expressionReport.addContent("Retrieving value of alpha1: " + evaluator->getExpressionResult("alpha1") + "\n");

	// expression valuator cannot handle sign operator
	// using expression that will evaluate to -1 for assignment
	expressionReport.addContent("Assigning result of -1 to variable gamma with expression: \n\t\"gamma = -1\"\n");
	evaluator->evaluateExpression("gamma = -1");
	expressionReport.addContent("Assigning value 2 to variable delta with expression: \n\t\"delta = 2\"\n");
	evaluator->evaluateExpression("delta = 2");

	expressionReport.addContent("\nRetrieving value of alpha: " + evaluator->getExpressionResult("alpha") + "\n");
	expressionReport.addContent("Retrieving value of beta: " + evaluator->getExpressionResult("beta") + "\n");
	expressionReport.addContent("Retrieving value of gamma: " + evaluator->getExpressionResult("gamma") + "\n");
	expressionReport.addContent("Retrieving value of delta: " + evaluator->getExpressionResult("delta") + "\n\n");

	expressionReport.addContent("Assigning alpha value of expression: \n\t\"alpha + beta / gamma * delta\"\n");
	evaluator->evaluateExpression("alpha = alpha + beta / gamma * delta");
	expressionReport.addContent("Retrieving value of alpha: " + evaluator->getExpressionResult("alpha") + "\n\n");

	expressionReport.addContent("Assigning beta value of expression: \n\t\"5 / 2.00 + alpha\"\n");
	evaluator->evaluateExpression("beta = 5 / 2.00 + alpha");
	expressionReport.addContent("Retrieving value of beta: " + evaluator->getExpressionResult("beta") + "\n\n");

	expressionReport.addContent("Assigning gamma value of expression: \n\t\"sin(alpha) + (gamma-delta) * 3\"\n");
	evaluator->evaluateExpression("gamma = sin(alpha) + (gamma-delta) * 3");
	expressionReport.addContent("Retrieving value of gamma: " + evaluator->getExpressionResult("gamma") + "\n\n");

	expressionReport.addContent("Assigning delta value of expression: \n\t\"alpha - beta * gamma / delta\"\n");
	evaluator->evaluateExpression("delta = alpha - beta * gamma / delta");
	expressionReport.addContent("Retrieving value of delta: " + evaluator->getExpressionResult("delta") + "\n\n");

	delete evaluator;

	expressionReport.saveReport(fileName);
}

/*
	Displays main menu with options and returns result of user selection
*/
int displayMainMenu()
{
	cout << "\n\n\n\n\t\t" << "Assignment 3 Expression Evaluator" << endl;
	cout << "\n\n\t" << "1 - Interactive Expression Evaluator" << endl;
	cout << "\t2 - Generate Expression Report" << endl;
	cout << "\tQ - Quit" << endl;
	cout << "\n\n\tChoice: ";

	char choice;
	cin >> choice;

	if ('Q' == choice || 'q' == choice)
	{
		return -1;
	}

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	return (int)choice - 48;
}

/*
	Displays an interactive expression evaluator menu,
		allows user to input an expression that will be evaluated,
		allows user to enter a variable that will show the current value,
		allows user to quit interactive expression evaluation.

		* - ExpressionEvaluator will throw exception on ill-formed expressions
*/
void displayInteractiveExpressionEvaluator()
{
	// ignoring "cin >> " call that took us to this menu
	cin.ignore();

	ExpressionEvaluator * evaluator = new ExpressionEvaluator();
	string userInput = "";
	bool continueExpressionEvaluation = true;

	while (true == continueExpressionEvaluation)
	{
		cout << "\tEnter an expression to evaluate, or\n\tVariable name to see current value, or\n\tQ to quit\n\n\t";

		cin.clear();
		// gets expression as user input
		getline(cin, userInput); 

		if ("Q" == userInput || "q" == userInput)
		{
			continueExpressionEvaluation = false;
		}
		else
		{
			// catch invalid_argument as ill-formed expressions
			try
			{
				string expressionResult = evaluator->getExpressionResult(userInput);
				cout << "\n\tEvaluated Result: " << expressionResult << "\n";
			}
			catch (const invalid_argument & ex)
			{
				cout << "\n\t" << ex.what() << "\n\n";
			}
		}
		cout << "\n\n\n\n";
	}

	delete evaluator;
}

void displayReportGenerator()
{
	// ignoring "cin >> " call that took us to this menu
	cin.ignore();

	cout << "\tGenerating report that will demonstrate capabilities of expression\nevaluator by evaluating each expression defined in assignment specification.\n\n";
	cout << "\tEnter filename or skip to use default (default 'expression-report.txt'): ";

	string filename;
	getline(cin, filename);

	if ("" == filename)
	{
		// uses default filename 'expression-report.txt'
		generateExpressionReport();
	}
	else
	{
		generateExpressionReport(filename);
	}

	cout << "\n\n\n\n";
}