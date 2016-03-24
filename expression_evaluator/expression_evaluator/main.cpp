#include "BinaryOperator.h"
#include "ExpressionEvaluator.h"
#include "List.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

int main(void)
{
	ExpressionEvaluator * evaluator = new ExpressionEvaluator();

	evaluator->setExpression("alpha = 5");
	evaluator->evaluateExpression();

	evaluator->getExpressionResult("alpha");

	evaluator->setExpression("beta = 10");
	evaluator->evaluateExpression();

	// expression valuator cannot handle sign operator
	// using expression that will evaluate to -1 for assignment
	evaluator->setExpression("gamma = 0 - 1");
	evaluator->evaluateExpression();

	evaluator->setExpression("delta = 2");
	evaluator->evaluateExpression();

	evaluator->setExpression("alpha = alpha + beta / gamma * delta");
	evaluator->evaluateExpression();

	evaluator->setExpression("beta = 5 / 2.00 + alpha");
	evaluator->evaluateExpression();

	evaluator->setExpression("gamma = sin(alpha) + (gamma-delta) * 3");
	evaluator->evaluateExpression();

	evaluator->setExpression("delta = alpha - beta * gamma / delta");
	evaluator->evaluateExpression();

	return 0;
}