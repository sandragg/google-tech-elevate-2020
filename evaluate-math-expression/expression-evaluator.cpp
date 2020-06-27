#include "expression-evaluator.h"
#include <exception>
#include <cmath>
#include <cstdlib>


namespace
{

bool is_digit(char c)
{
	return c >= '0' && c <='9';
}

double read_number(const std::string &str, size_t pos, size_t& amount)
{
	auto *begin = &str[pos];
	char *end = nullptr;
	auto number = strtod(begin, &end);
	amount = end - begin;
	return number;
}

std::string read_operation(const std::string &str, size_t pos, size_t& amount)
{
	std::string operation;
	for (auto i = pos; i < str.size(); i++)
	{
		auto c = str[i];
		if (is_digit(c) || c == '.' || c == '(' || c == ')') break;

		operation.push_back(c);
		if (c < 'A' || c > 'z') break;
	}
	amount = operation.size();

	return operation;
}

} // anonymous


namespace math
{

std::unordered_map<std::string, OperationPair> ExpressionEvaluator::pattern_to_code_pair;
std::unordered_map<OperationCode, UnaryOperation> ExpressionEvaluator::code_to_unary_operation;
std::unordered_map<OperationCode, BinaryOperation> ExpressionEvaluator::code_to_binary_operation;


ExpressionEvaluator::ExpressionEvaluator(std::string input)
{
	const auto &[ expr, valid ] = parse_and_validate(input);

	if (!valid) throw std::invalid_argument("Invalid mathematical expression.");
	expression = expr;
}

double ExpressionEvaluator::Evaluate() const
{
	std::stack<OperationCode> operators;
	std::stack<double> output;

	for (size_t i = 0; i < expression.size(); i++)
	{
		const auto c = expression[i];

		if (c == '(')
		{
			operators.push(OperationCode::LEFT_BRACKET);
			continue;
		}
		if (c == ')')
		{
			evaluate_while(operators, output,
				[](OperationCode code) { return code != OperationCode::LEFT_BRACKET; });
			operators.pop();
			continue;
		}
		if (is_digit(c) || c == '.')
		{
			size_t amount_of_processed = 0;
			auto value = read_number(expression, i, amount_of_processed);
			output.push(value);
			i += amount_of_processed - 1;
			continue;
		}

		size_t amount_of_processed = 0;
		auto pattern = read_operation(expression, i, amount_of_processed);
		auto [ unary, binary ] = pattern_to_code_pair.at(pattern);

		if (unary != OperationCode::INVALID && code_to_unary_operation.count(unary))
		{
			const auto& operation = code_to_unary_operation[unary];
			if (operation.associativity == Associativity::Left
				|| !i
				|| (!is_digit(expression[i - 1]) && operators.top() != OperationCode::RIGHT_BRACKET)) // no operand before operator
			{
				operators.push(unary);
				i += amount_of_processed - 1;
				continue;
			}
		}

		const auto& operation = code_to_binary_operation[binary];
		if (operation.associativity == Associativity::Left)
		{
			evaluate_while(operators, output,
				[&operation](OperationCode code)
				{
				   if (code == OperationCode::LEFT_BRACKET) return false;
				   auto precedence = code_to_unary_operation.count(code)
						? code_to_unary_operation.at(code).precedence
						: code_to_binary_operation.at(code).precedence;
				   return precedence >= operation.precedence;
				});
		}
		operators.push(binary);
		i += amount_of_processed - 1;
	}
	evaluate_while(operators, output, [](OperationCode){ return true; });

	return output.top();
}

std::pair<std::string, bool> ExpressionEvaluator::parse_and_validate(const std::string &expr) const
{
	std::string parsed_expression;

	// TODO Add validation
	for (const auto c : expr)
	{
		if (c != ' ') parsed_expression.push_back(c);
	}

	return { parsed_expression, true };
}

template <class Condition>
void ExpressionEvaluator::evaluate_while(
	std::stack<OperationCode> &operators,
	std::stack<double> &operands,
	Condition should_evaluate) const
{
	try {
		while (!operators.empty() && should_evaluate(operators.top()))
		{
			auto operation_code = operators.top();
			operators.pop();
			auto rhs = operands.top();
			operands.pop();

			if (code_to_unary_operation.count(operation_code))
			{
				const auto& operation = code_to_unary_operation.at(operation_code);
				if (!operation.Validate(rhs))
					throw std::exception();
				operands.push(operation.Evaluate(rhs));
			}
			else
			{
				auto lhs = operands.top();
				operands.pop();
				const auto& operation = code_to_binary_operation.at(operation_code);
				if (!operation.Validate(lhs, rhs))
					throw std::exception();
				operands.push(operation.Evaluate(lhs, rhs));
			}
		}
	}
	catch (std::exception&)
	{
		throw std::invalid_argument("Invalid mathematical expression.");
	}
}

void ExpressionEvaluator::initialize_operations(
	const std::vector<math::UnaryOperation> &unary_operations,
	const std::vector<math::BinaryOperation> &binary_operations)
{
	for (const auto& operation : unary_operations)
	{
		pattern_to_code_pair.insert(
			{
				operation.pattern,
				OperationPair { operation.id, OperationCode::INVALID }
			});
		code_to_unary_operation.insert({ operation.id, operation });
	}

	for (const auto& operation : binary_operations)
	{
		const auto &pattern = operation.pattern;

		if (pattern_to_code_pair.count(pattern))
		{
			pattern_to_code_pair[pattern].binary = operation.id;
		}
		else
		{
			pattern_to_code_pair.insert(
				{
					pattern,
					{ OperationCode::INVALID, operation.id }
				});
		}
		code_to_binary_operation.insert({ operation.id, operation });
	}
}

double round_to_n_places(double value, int decimal_places)
{
	double factor = std::pow(10, decimal_places);
	return round(value * factor) / factor;
}

} // math
