#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../Expression/Expression.h"

SCENARIO("Calculate polish notation positive tests")
{
	GIVEN("Operation with one argument")
	{
		std::string input("(+ 7)");

		THEN("The value of expression is equal to the argument")
		{
			CHECK(CalculatePolish(input) == 7);
		}
	}

	GIVEN("Operation with many arguments")
	{
		std::string input("(/ 32 4 2)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 4);
		}
	}

	GIVEN("Expression with one argument, which is an expression")
	{
		std::string input("(+ (* 1 3 8))");

		THEN("The outer operation does not affect the value of the expression inside")
		{
			CHECK(CalculatePolish(input) == 24);
		}
	}

	GIVEN("Expression with one argument and expression inside")
	{
		std::string input("(- 25 (* 1 3 8))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with one expression and argument inside")
	{
		std::string input("(- (* 1 3 8) 23)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with two expressions inside")
	{
		std::string input("(- (* 1 3 8) (+ 20 3))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Double nested expression")
	{
		std::string input("(+ 5 (* 2 3 2) (+ 5 (+ 2 5) (* 2 2)))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 33);
		}
	}

	GIVEN("Strongly nested expression")
	{
		std::string input("(* 2 (* 2 (* 2 (* 2 (* 2 (* 2))))))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 64);
		}
	}

	GIVEN("Expression with negative argument")
	{
		std::string input("(+ -2 3)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with negative argument and negative result")
	{
		std::string input("(+ -2 (* -1 (/ 27 -9)) -2)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == -1);
		}
	}

	GIVEN("Expression with fractions")
	{
		std::string input("(+ 0.5 0.5)");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == 1);
		}
	}

	GIVEN("Expression with fractions (extended)")
	{
		std::string input("(/ (+ -20.33 4.13 6.20) (* (/ 32.5 16.25) 2))");

		THEN("Expression calculated correctly")
		{
			CHECK(CalculatePolish(input) == -2.5);
		}
	}
}

SCENARIO("Calculate polish notation negative tests")
{
	GIVEN("Single argument")
	{
		std::string input = "25";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Letters")
	{
		std::string input = "ABC";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Expression without operation")
	{
		std::string input = "(1 2 3)";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Operation without arguments")
	{
		std::string input = "(+)";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Number of opening parenthesis is greater than closing")
	{
		std::string input = "(+ 2 (+ 2 (+ 2))";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Number of closing parenthesis is greater than opening")
	{
		std::string input = "(+ 2 (+ 2 (+ 2))))";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Expression without one parenthesis pair")
	{
		std::string input = "(+ 2 + 2 (+ 2))";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}

	GIVEN("Expression with letter")
	{
		std::string input = "(* 8 (- 9 a) 1)";

		THEN("Exception was thrown")
		{
			CHECK_THROWS_AS(CalculatePolish(input), std::invalid_argument);
		}
	}
}