#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>


namespace math
{

enum Associativity
{
	Left,
	Right
};

enum Arity
{
	Unary,
	Binary
};

enum OperationCode
{
	INVALID,
	LEFT_BRACKET,
	RIGHT_BRACKET,
	PLUS_B,
	MINUS_B,
	MINUS_U,
	MULTI,
	DIVISION,
	PWR,
	ABS,
	SQRT
};

struct Operation
{
	OperationCode id;
	size_t precedence;
	Associativity associativity;
	Arity arity;
	std::string pattern;
};

class UnaryOperation : public Operation
{
	public:
		using evaluate = double(*)(double);
		using check_validity = bool (*)(double);

		UnaryOperation() = default;
		UnaryOperation(
			OperationCode id,
			size_t priority,
			Associativity associativity,
			std::string pattern,
			evaluate eval,
			check_validity validate = nullptr);

		bool Validate(double operand) const;
		double Evaluate(double operand) const;

	private:
		evaluate eval;
		check_validity validate;
};

class BinaryOperation : public Operation
{
	public:
		using evaluate = double(*)(double, double);
		using check_validity = bool (*)(double, double);

		BinaryOperation() = default;
		BinaryOperation(
			OperationCode id,
			size_t priority,
			Associativity associativity,
			std::string pattern,
			evaluate eval,
			check_validity validate = nullptr);

		bool Validate(double lhs, double rhs) const;
		double Evaluate(double lhs, double rhs) const;

	private:
		evaluate eval;
		check_validity validate;
};

struct OperationPair
{
	OperationCode unary;
	OperationCode binary;
};

extern const std::vector<UnaryOperation> unary_operation;
extern const std::vector<BinaryOperation> binary_operation;

} // namespace math


#endif //OPERATIONS_H
