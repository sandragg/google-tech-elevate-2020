#include "operations.h"


namespace math
{

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
