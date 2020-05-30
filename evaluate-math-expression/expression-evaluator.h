#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <iostream>
#include <stack>
#include <map>
#include "operations.h"


namespace math
{

class ExpressionEvaluator
{
	public:
		ExpressionEvaluator(std::string input);
		float Evaluate();

	private:
		std::string expression;
		std::stack<OperationCode> operators;
		std::stack<float> output;
};

} // namespace math


#endif //EXPRESSION_EVALUATOR_H
