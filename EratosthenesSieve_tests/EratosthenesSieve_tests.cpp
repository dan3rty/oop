#include <iostream>
#include <set>
#include <string>
#define CATCH_CONFIG_MAIN
#include "../EratosthenesSieve/EratosthenesSieve.h"
#include "../catch2/catch.hpp"
#include <boost/timer.hpp>

const constexpr int MAX_UPPER_BOUND = 100000000;

TEST_CASE("Get prime numbers with negative upper bound")
{
	int input = -5;
	std::string expectedErrorMessage = "Upper bound can not be negative number";
	CHECK_THROWS_WITH(GeneratePrimeNumbersSet(input), expectedErrorMessage);
}

TEST_CASE("Get prime numbers with overbound input value")
{
	int input = 100000001;
	std::string expectedErrorMessage = "The upper limit shall not exceed 100000000";
	CHECK_THROWS_WITH(ValidateUpperBound(input), expectedErrorMessage);
}

TEST_CASE("Get prime numbers with upper bound = 0")
{
	int input = 0;
	std::set<int> expected = { };
	std::set<int> result = GeneratePrimeNumbersSet(input);
	CHECK(result == expected);
}

TEST_CASE("Get prime numbers with upper bound = 50")
{
	int input = 123;
	std::set<int> expected = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
	std::set<int> result = GeneratePrimeNumbersSet(input);
	CHECK(result == expected);
}

TEST_CASE("Get prime numbers with upper bound equals to last prime number in set")
{
	int input = 11;
	std::set<int> expected = { 2, 3, 5, 7, 11 };
	std::set<int> result = GeneratePrimeNumbersSet(input);
	CHECK(result == expected);
}

#ifdef NDEBUG
TEST_CASE("Testing max upper bound")
{
	int input = MAX_UPPER_BOUND;
	size_t expectedCount = 5761455;
	std::set<int> result = GeneratePrimeNumbersSet(input);
	size_t resultCount = result.size();
	CHECK(resultCount == expectedCount);
}

TEST_CASE("Runtime testing")
{
	boost::timer t;
	int input = MAX_UPPER_BOUND;
	t.restart();
	GeneratePrimeNumbersSet(input);
	double runtime = t.elapsed();
	std::cout << "Time: " << runtime << std::endl;
	double maxRuntime = 6;
	CHECK(runtime <= maxRuntime);
}
#endif
