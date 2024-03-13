#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"
#include "../Radix/Radix.h"
#include <climits>
#include <format>

constexpr const int DECIMAL = 10;
constexpr const int MIN_RADIX = 2;
constexpr const int MAX_RADIX = 36;

TEST_CASE("Changing MININT notation")
{
	std::string input = "-80000000";
	int inputRadix = 16;
	std::string expected = "-2147483648";
	std::string result = ChangeNumberNotation(inputRadix, DECIMAL, input);
	REQUIRE(result == expected);
}

TEST_CASE("Changing MAXINT conversion")
{
	std::string input = "7FFFFFFF";
	int inputRadix = 16;
	std::string expected = "2147483647";
	std::string result = ChangeNumberNotation(inputRadix, DECIMAL, input);
	REQUIRE(result == expected);
}

TEST_CASE("Average number")
{
	std::string input = "500";
	int inputRadix = 16;
	std::string expected = "1F4"; 
	std::string result = ChangeNumberNotation(DECIMAL, inputRadix, input);
	REQUIRE(result == expected);
}

TEST_CASE("Negative Number")
{
	std::string input = "-10";
	int inputRadix = 10;
	std::string expected = "-10";
	std::string result = ChangeNumberNotation(inputRadix, inputRadix, input);
	REQUIRE(result == expected);
}

TEST_CASE("Number that overflows int")
{
	std::string input = "80000000";
	int inputRadix = 16;
	std::string expectedExceptionMessage = "Overflow occured";
	REQUIRE_THROWS_WITH(ChangeNumberNotation(inputRadix, inputRadix, input), expectedExceptionMessage);
}

TEST_CASE("Number with digit, that unsupported by the notation")
{
	std::string input = "333";
	int inputRadix = 2;
	std::string expectedExceptionMessage =
		std::format("The digit \"{}\" is not supported by the number system \"{}\"", input[0], inputRadix);
	REQUIRE_THROWS_WITH(ChangeNumberNotation(inputRadix, inputRadix, input), expectedExceptionMessage);
}

TEST_CASE("Convertion with wrong notation")
{
	std::string input = "1";
	int inputRadix = 50;
	std::string expectedExceptionMessage = 
		std::format("Notations should be between {} and {}", MIN_RADIX, MAX_RADIX);
	REQUIRE_THROWS_WITH(ChangeNumberNotation(inputRadix, inputRadix, input), expectedExceptionMessage);
}