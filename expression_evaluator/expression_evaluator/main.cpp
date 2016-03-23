#include "BinaryOperator.h"
#include "ExpressionEvaluator.h"
#include "List.h"
#include "Operand.h"

using namespace psands_cisp430_a2;
using namespace psands_cisp430_a3;

double add(double a, double b)
{
	return a + b;
}

int main(void)
{
	//BinaryOperator * bo = new BinaryOperator(add);

	//List<Operand *> * operands = new List<Operand *>();
	//operands->add(new Operand(10));
	//operands->add(new Operand(5));

	//bo->Evaluate(operands);

	ExpressionEvaluator * evaluator = new ExpressionEvaluator();

	evaluator->setExpression("A = A * (B + C) / D");
	evaluator->getExpressionResult();

	return 0;
}