#include "operations.h"


namespace math
{

extern const std::unordered_map<std::string, UnaryOperation> value_to_unary_operation({
	{
	   "-",
	   UnaryOperation(OperationCode::MINUS_U, 3, Associativity::Right,
			[](float v){ return -v; })
	},
	{
		"abs",
		UnaryOperation(OperationCode::ABS, 3, Associativity::Right,
			[](float v){ return std::fabs(v); })
	},
	{
		"sqrt",
		UnaryOperation(OperationCode::SQRT, 3, Associativity::Right,
			[](float v){ return std::sqrt(v); },
			[](float v){ return v >= 0; })
	}
});

extern const std::unordered_map<std::string, BinaryOperation> value_to_binary_operation({
	{
		"+",
		BinaryOperation(OperationCode::PLUS_B, 1, Associativity::Left,
			[](float lhs, float rhs){ return lhs + rhs; })
	},
	{
		"-",
		BinaryOperation(OperationCode::MINUS_B, 1, Associativity::Left,
			[](float lhs, float rhs){ return lhs - rhs; })
	},
	{
		"*",
		BinaryOperation(OperationCode::MULTI, 2, Associativity::Left,
			[](float lhs, float rhs){ return lhs * rhs; })
	},
	{
		"/",
		BinaryOperation(OperationCode::DIVISION, 2, Associativity::Left,
			[](float lhs, float rhs){ return lhs / rhs; },
			[](float lhs, float rhs){ return rhs != 0; })
	},
	{
		"^",
		BinaryOperation(OperationCode::PWR, 4, Associativity::Right,
			[](float lhs, float rhs){ return std::pow(lhs, rhs); },
			[](float lhs, float rhs){ return lhs >= 0; })
	}
});

UnaryOperation::UnaryOperation(
	OperationCode id,
	size_t priority,
	Associativity associativity,
	UnaryOperation::evaluate eval,
	UnaryOperation::check_validity validate)
{
	this->id = id;
	this->precedence = priority;
	this->associativity = associativity;
	this->arity = Arity::Unary;

	this->eval = eval;
	this->validate = validate;
}

bool UnaryOperation::Validate(float operand) const
{
	return validate ? validate(operand) : true;

}

float UnaryOperation::Evaluate(float operand) const
{
	return eval(operand);
}

BinaryOperation::BinaryOperation(
	OperationCode id,
	size_t priority,
	Associativity associativity,
	BinaryOperation::evaluate eval,
	BinaryOperation::check_validity validate)
{
	this->id = id;
	this->precedence = priority;
	this->associativity = associativity;
	this->arity = Arity::Binary;

	this->eval = eval;
	this->validate = validate;
}

bool BinaryOperation::Validate(float lhs, float rhs) const
{
	return validate ? validate(lhs, rhs) : true;
}

float BinaryOperation::Evaluate(float lhs, float rhs) const
{
	return eval(lhs, rhs);
}

}
