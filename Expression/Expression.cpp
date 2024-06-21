#include <functional>
#include <numeric>
#include <sstream>
#include <stack>
#include <vector>
#include "Expression.h"

namespace
{
using Arguments = std::vector<double>;

enum class Operation
{
	Add,
	Sub,
	Mult,
	Div
};

struct Expression
{
	Operation operation;
	Arguments args = {};
};

using ExprStack = std::stack<Expression>;

Operation GetOperation(char ch)
{
	switch (ch)
	{
	case '+':
		return Operation::Add;
	case '-':
		return Operation::Sub;
	case '*':
		return Operation::Mult;
	case '/':
		return Operation::Div;
	default:
		throw std::invalid_argument("Unknown operation " + ch);
	}
}

void ValidateExpression(Expression const& expr)
{
	if (expr.args.empty())
	{
		throw std::invalid_argument("Operation without arguments not allowed");
	}
}

template <class T>
double ReduceArgs(Arguments const& v, T operation)
{
	return std::reduce(v.begin() + 1, v.end(), v[0], operation);
}

double CalculateExpression(Expression const& expr)
{
	ValidateExpression(expr);
	switch (expr.operation)
	{
	case Operation::Add:
		return ReduceArgs(expr.args, std::plus<double>());
	case Operation::Sub:
		return ReduceArgs(expr.args, std::minus<double>());
	case Operation::Mult:
		return ReduceArgs(expr.args, std::multiplies<double>());
	case Operation::Div:
		return ReduceArgs(expr.args, std::divides<double>());
	}
	throw std::invalid_argument("Unknown operation");
}

Expression ReadExpression(std::istream& input)
{
	char ch;
	input >> ch;
	Expression expr{ GetOperation(ch) };
	while (input >> ch)
	{
		//выяснить и доложить (выяснено)
		input.unget();
		if (ch == ')' || ch == '(')
		{
			return expr;
		}
		double arg;
		input >> arg;
		expr.args.push_back(arg);
	}

	throw std::invalid_argument("Some expression was opened but was not closed");
}

//rename
double FoldExpression(ExprStack& stack)
{
	if (stack.empty())
	{
		throw std::invalid_argument("Some expression was closed but was not opened");
	}
	double value = CalculateExpression(stack.top());
	stack.pop();
	if (!stack.empty())
	{
		stack.top().args.push_back(value);
	}
	return value;
}

//можно ли вынести два чтения аргумента в одну функцию?
void ReadArgument(std::istream& input, ExprStack& stack)
{
	//неочевидный unget (исправлено)
	double value;
	input >> value;
	stack.top().args.push_back(value);
}

void ValidateFirstChar(std::istream& input)
{
	char ch;
	input >> ch;
	if (ch != '(')
	{
		throw std::invalid_argument("Expression must start with (");
	}
	input.unget();
}

void CheckStackIsEmpty(ExprStack& stack)
{
	if (!stack.empty())
	{
		throw std::invalid_argument("Some expression was opened but was not closed");
	}
}
} // namespace

double CalculatePolish(const std::string& inputStr)
{
	std::istringstream input(inputStr);
	ValidateFirstChar(input);
	ExprStack stack;
	double value = 0;
	char ch;
	while (input >> ch)
	{
		if (ch == '(')
		{
			stack.push(ReadExpression(input));
		}
		else if (ch == ')')
		{
			value = FoldExpression(stack);
		}
		else
		{
			input.unget();
			ReadArgument(input, stack);
		}
	}
	CheckStackIsEmpty(stack);

	return value;
}