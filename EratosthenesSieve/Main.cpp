#include "EratosthenesSieve.h"
#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <exception>

struct Args
{
	std::string inputUpperBound;
};

Args ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Usage: EratosthenesSieve.exe <upper_bound>");
	}
	Args args;
	args.inputUpperBound = argv[1];
	return args;
}

int main(int argc, char* argv[])
{
	std::set<int> primeNumbers;
	try
	{
		auto args = ParseArgs(argc, argv);
		int upperBound = std::stoi(args.inputUpperBound);
		ValidateUpperBound(upperBound);
		primeNumbers = GeneratePrimeNumbersSet(upperBound);

	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	std::ranges::copy(primeNumbers, std::ostream_iterator<int>(std::cout, " "));

	return EXIT_SUCCESS;
}
