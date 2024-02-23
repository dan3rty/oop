#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../Radix/Radix.h"
#include "climits"

TEST_CASE("String replacement with possible looping")
{
	std::string inputString = "A";
	int inputRadix = 16;
	int expected = 10;
	int result = StringToInt(inputString, inputRadix);
	REQUIRE(result == expected);
}

TEST_CASE("MAXINT + 1")
{
	std::string inputString = "80000000";
	size_t inputRadix = 16;
	size_t expected = INT_MIN;
	size_t result = StringToInt(inputString, inputRadix);
	REQUIRE(result == expected);
}

TEST_CASE("Normal string to number")
{
	size_t inputNumber = 500;
	size_t inputRadix = 16;
	std::string expected = "1F4"; 
	std::string result = IntToString(inputNumber, inputRadix);
	REQUIRE(result == expected);
}

TEST_CASE("Negative Number")
{
	std::string input = "-10";
	std::string inputRadix = "10";
	std::string expected = "-10";
	std::string result = numberConversion(inputRadix, inputRadix, input);
	REQUIRE(result == expected);
}

