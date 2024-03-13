#include "../Invert/Invert.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

TEST_CASE("Get invert matrix from valid input")
{
	std::istringstream input(
		"2  5  7\n"
		"6  3  4\n"
		"5  -2  -3\n"
	);
	auto inputMatrix = ReadMatrixFromStream(input);
	auto result = InvertMatrix(inputMatrix);
	TripleMatrix expected = { { 
		{ 1, -1, 1 },
		{ -38, 41, -34 },
		{ 27, -29, 24 } 
		} };
	REQUIRE(result.value() == expected);
}

TEST_CASE("Get matrix from invalid input")
{
	std::istringstream input(
		"2  5\n"
		"6  3\n"
	);
	std::string expectedErrorMessage = "Invalid matrix";
	REQUIRE_THROWS_WITH(ReadMatrixFromStream(input), expectedErrorMessage);
}

TEST_CASE("Get invert matrix with a zero determinant")
{
	std::istringstream input(
		"1  1  1\n"
		"1  1  1\n"
		"1  1  1\n"
	);
	auto inputMatrix = ReadMatrixFromStream(input);
	auto result = InvertMatrix(inputMatrix);
	REQUIRE(result.has_value() == false);
}

TEST_CASE("Get matrix from valid input")
{
	std::istringstream input(
		"2  5  7\n"
		"6  3  4\n"
		"5  -2  -3\n");
	auto inputMatrix = ReadMatrixFromStream(input);
	TripleMatrix expected = { { 
		{ 2, 5, 7 },
		{ 6, 3, 4 },
		{ 5, -2, -3 } 
		} };
	REQUIRE(inputMatrix == expected);
}