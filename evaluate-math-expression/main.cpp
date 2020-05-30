#include <iostream>
#include <string>
#include "expression-evaluator.h"


int main() {
	std::string expression;
	std::getline(std::cin, expression);
	std::cout << math::ExpressionEvaluator(expression).Evaluate() << std::endl;
}
