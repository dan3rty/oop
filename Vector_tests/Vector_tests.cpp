#include "../vector/Vector.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

TEST_CASE("Read vector from input")
{
	std::istringstream input("2.5 5.5 1.0 4 13");
	std::vector<double> result = ParseDoublesToVector(input);
	std::vector<double> expected = {2.5, 5.5, 1, 4, 13};
	REQUIRE(result == expected);
}

TEST_CASE("Average vector processing")
{
	std::istringstream input("2.5 5.5 2 4 13");
	std::vector<double> result = ParseDoublesToVector(input);
	MultElementsByMin(result);
	std::vector<double> expected = { 5, 11, 4, 8, 26 };
	REQUIRE(result == expected);
}

TEST_CASE("Processing of vector with negative min value")
{
	std::istringstream input("2.5 5.5 -2 4 13");
	std::vector<double> result = ParseDoublesToVector(input);
	MultElementsByMin(result);
	std::vector<double> expected = { -5, -11, 4, -8, -26 };
	REQUIRE(result == expected);
}

TEST_CASE("Processing of vector with min value equal to zero")
{
	std::istringstream input("2.5 5.5 0 4 13");
	std::vector<double> result = ParseDoublesToVector(input);
	MultElementsByMin(result);
	std::vector<double> expected = { 0, 0, 0, 0, 0 };
	REQUIRE(result == expected);
}