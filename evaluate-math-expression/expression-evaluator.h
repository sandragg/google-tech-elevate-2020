#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include <utility>
#include "operations.h"


namespace math
{

double round_to_n_places(double value, uint16_t decimal_places);
bool is_digit(char c);

class ExpressionEvaluator
{
	public:
		explicit ExpressionEvaluator(std::string input);
		double Evaluate();

		static void initialize_operations(
			const std::vector<math::UnaryOperation> &unary_operations,
			const std::vector<math::BinaryOperation> &binary_operations);

	private:
		std::string expression;

		std::pair<std::string, bool> parse_and_validate(const std::string &expr) const;
		double read_number(const std::string &str, size_t pos, size_t& amount) const;
		std::string read_operation(const std::string &str, size_t pos, size_t& amount) const;

		template <class Condition>
		void evaluate_while(
			std::stack<OperationCode> &operators,
			std::stack<double> &operands,
			Condition should_evaluate) const;

		static std::unordered_map<std::string, OperationPair> pattern_to_code_pair;
		static std::unordered_map<OperationCode, UnaryOperation> code_to_unary_operation;
		static std::unordered_map<OperationCode, BinaryOperation> code_to_binary_operation;
};

} // namespace math


#endif //EXPRESSION_EVALUATOR_H
