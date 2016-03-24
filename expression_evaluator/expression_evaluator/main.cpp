// Author: Peter Sands - W1541805
// Course: CISP 430 - Wed 6:30
// Spring 2016
// Assign 3

#include <string>
#include "ExpressionEvaluator.h"
#include "Report.h"

using namespace std;
using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

string getReportHeader();
void generateExpressionReport(char * fileName);

/*
	Goal: Demonstrate expression evaluation and variable assignment by generating report
		that evaluates expressions defined in assignment spec.

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
		
*/
int main(void)
{
	generateExpressionReport("C:\\Users\\peter\\Documents\\rep\\expression-report.txt");

	return 0;
}

string getReportHeader()
{
	return "Peter Sands\nW1541805\nCISP 430 WED 6:30\nSpring 2016\nAssign 3\n";
}

void generateExpressionReport(char * fileName)
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
	expressionReport.addContent("Retrieving value of alpha1: " + to_string(evaluator->getExpressionResult("alpha1")) + "\n");

	// expression valuator cannot handle sign operator
	// using expression that will evaluate to -1 for assignment
	expressionReport.addContent("Assigning result of 0-1 (-1) to variable gamma with expression: \n\t\"gamma = 0 - 1\"\n");
	evaluator->evaluateExpression("gamma = 0 - 1");
	expressionReport.addContent("Assigning value 2 to variable delta with expression: \n\t\"delta = 2\"\n");
	evaluator->evaluateExpression("delta = 2");

	expressionReport.addContent("\nRetrieving value of alpha: " + to_string(evaluator->getExpressionResult("alpha")) + "\n");
	expressionReport.addContent("Retrieving value of beta: " + to_string(evaluator->getExpressionResult("beta")) + "\n");
	expressionReport.addContent("Retrieving value of gamma: " + to_string(evaluator->getExpressionResult("gamma")) + "\n");
	expressionReport.addContent("Retrieving value of delta: " + to_string(evaluator->getExpressionResult("delta")) + "\n\n");

	expressionReport.addContent("Assigning alpha value of expression: \n\t\"alpha + beta / gamma * delta\"\n");
	evaluator->evaluateExpression("alpha = alpha + beta / gamma * delta");
	expressionReport.addContent("Retrieving value of alpha: " + to_string(evaluator->getExpressionResult("alpha")) + "\n\n");

	expressionReport.addContent("Assigning beta value of expression: \n\t\"5 / 2.00 + alpha\"\n");
	evaluator->evaluateExpression("beta = 5 / 2.00 + alpha");
	expressionReport.addContent("Retrieving value of beta: " + to_string(evaluator->getExpressionResult("beta")) + "\n\n");

	expressionReport.addContent("Assigning gamma value of expression: \n\t\"sin(alpha) + (gamma-delta) * 3\"\n");
	evaluator->evaluateExpression("gamma = sin(alpha) + (gamma-delta) * 3");
	expressionReport.addContent("Retrieving value of gamma: " + to_string(evaluator->getExpressionResult("gamma")) + "\n\n");

	expressionReport.addContent("Assigning delta value of expression: \n\t\"alpha - beta * gamma / delta\"\n");
	evaluator->evaluateExpression("delta = alpha - beta * gamma / delta");
	expressionReport.addContent("Retrieving value of delta: " + to_string(evaluator->getExpressionResult("delta")) + "\n\n");

	expressionReport.saveReport(fileName);
}