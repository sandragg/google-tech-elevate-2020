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
};

class UnaryOperation : public Operation
{
	public:
		using evaluate = float(*)(float);
		using check_validity = bool (*)(float);

		UnaryOperation(
			OperationCode id,
			size_t priority,
			Associativity associativity,
			evaluate eval,
			check_validity validate = nullptr);

		bool Validate(float operand) const;
		float Evaluate(float operand) const;

	private:
		evaluate eval;
		check_validity validate;
};

class BinaryOperation : public Operation
{
	public:
		using evaluate = float(*)(float, float);
		using check_validity = bool (*)(float, float);

		BinaryOperation(
			OperationCode id,
			size_t priority,
			Associativity associativity,
			evaluate eval,
			check_validity validate = nullptr);

		bool Validate(float lhs, float rhs) const;
		float Evaluate(float lhs, float rhs) const;

	private:
		evaluate eval;
		check_validity validate;
};

extern const std::unordered_map<std::string, UnaryOperation> value_to_unary_operation;
extern const std::unordered_map<std::string, BinaryOperation> value_to_binary_operation;

} // namespace math


#endif //OPERATIONS_H
