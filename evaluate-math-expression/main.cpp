#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include "expression-evaluator.h"


int main() {
	math::ExpressionEvaluator::initialize_operations();
	std::string expression;
	std::getline(std::cin, expression);

	try {
		auto evaluator = math::ExpressionEvaluator(expression);
		auto value = evaluator.Evaluate();
		std::cout
			<< std::fixed
			<< std::setprecision(2)
			<< math::round_to_n_places(value, 2)
			<< std::endl;
	}
	catch (std::exception &err)
	{
		std::cout << err.what() << std::endl;
	}

	return 0;
}
