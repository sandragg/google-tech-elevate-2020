#include <iostream>
#include <string>
#include <exception>
#include <iomanip>
#include "expression-evaluator.h"


namespace
{
	void init_unary_operations(std::vector<math::UnaryOperation> &operations)
	{
		using namespace math;

		operations.assign({
			UnaryOperation(OperationCode::MINUS_U, 3, Associativity::Right, "-",
				 [](double v){ return -v; }),

			UnaryOperation(OperationCode::ABS, 3, Associativity::Right, "abs",
				 [](double v){ return std::fabs(v); }),

			UnaryOperation(OperationCode::SQRT, 3, Associativity::Right, "sqrt",
				 [](double v){ return std::sqrt(v); },
				 [](double v){ return v >= 0; })
		});
	}

	void init_binary_operations(std::vector<math::BinaryOperation> &operations)
	{
		using namespace math;

		operations.assign({
			BinaryOperation(OperationCode::PLUS_B, 1, Associativity::Left, "+",
				[](double lhs, double rhs){ return lhs + rhs; }),

			BinaryOperation(OperationCode::MINUS_B, 1, Associativity::Left, "-",
				[](double lhs, double rhs){ return lhs - rhs; }),

			BinaryOperation(OperationCode::MULTI, 2, Associativity::Left, "*",
				[](double lhs, double rhs){ return lhs * rhs; }),

			BinaryOperation(OperationCode::DIVISION, 2, Associativity::Left, "/",
				[](double lhs, double rhs){ return lhs / rhs; },
				[](double lhs, double rhs){ return rhs != 0; }),

			BinaryOperation(OperationCode::PWR, 4, Associativity::Right, "^",
				  [](double lhs, double rhs){ return std::pow(lhs, rhs); },
				  [](double lhs, double rhs){ return lhs >= 0; })
		});
	}
}

int main()
{
	std::vector<math::UnaryOperation> unary_operations;
	init_unary_operations(unary_operations);
	std::vector<math::BinaryOperation> binary_operations;
	init_binary_operations(binary_operations);
	math::ExpressionEvaluator::initialize_operations(unary_operations, binary_operations);

	std::string expression;
	std::getline(std::cin, expression);

	try {
		math::ExpressionEvaluator evaluator(expression);
		auto value = evaluator.Evaluate();
		int precision = 2;
		std::cout
			<< std::fixed
			<< std::setprecision(precision)
			<< math::round_to_n_places(value, precision)
			<< std::endl;
	}
	catch (std::exception &err)
	{
		std::cout << err.what() << std::endl;
	}

	return 0;
}
