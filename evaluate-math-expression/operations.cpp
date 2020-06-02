#include "operations.h"


namespace math
{

extern const std::vector<UnaryOperation> unary_operation({
	UnaryOperation(OperationCode::MINUS_U, 3, Associativity::Right, "-",
		[](double v){ return -v; }),

	UnaryOperation(OperationCode::ABS, 3, Associativity::Right, "abs",
		[](double v){ return std::fabs(v); }),

	UnaryOperation(OperationCode::SQRT, 3, Associativity::Right, "sqrt",
		[](double v){ return std::sqrt(v); },
		[](double v){ return v >= 0; })
});

extern const std::vector<BinaryOperation> binary_operation({
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

UnaryOperation::UnaryOperation(
	OperationCode id,
	size_t priority,
	Associativity associativity,
	std::string pattern,
	UnaryOperation::evaluate eval,
	UnaryOperation::check_validity validate)
{
	this->id = id;
	this->precedence = priority;
	this->associativity = associativity;
	this->arity = Arity::Unary;
	this->pattern = pattern;

	this->eval = eval;
	this->validate = validate;
}

bool UnaryOperation::Validate(double operand) const
{
	return validate ? validate(operand) : true;

}

double UnaryOperation::Evaluate(double operand) const
{
	return eval(operand);
}

BinaryOperation::BinaryOperation(
	OperationCode id,
	size_t priority,
	Associativity associativity,
	std::string pattern,
	BinaryOperation::evaluate eval,
	BinaryOperation::check_validity validate)
{
	this->id = id;
	this->precedence = priority;
	this->associativity = associativity;
	this->arity = Arity::Binary;
	this->pattern = pattern;

	this->eval = eval;
	this->validate = validate;
}

bool BinaryOperation::Validate(double lhs, double rhs) const
{
	return validate ? validate(lhs, rhs) : true;
}

double BinaryOperation::Evaluate(double lhs, double rhs) const
{
	return eval(lhs, rhs);
}

} // math
