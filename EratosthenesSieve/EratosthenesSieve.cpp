#include <iostream>
#include <set>
#include <vector>
#include <exception>
#include <climits>

const constexpr int MAX_UPPER_BOUND = 100000000;

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	if (upperBound < 0)
	{
		throw std::invalid_argument("Upper bound can not be negative number");
	}

	std::vector<bool> isPrime(upperBound + 1, true);
	std::set<int> primeNumbers;

	for (int i = 2; i <= upperBound; ++i)
	{
		if (isPrime[i])
		{
			primeNumbers.insert(primeNumbers.end(), i);
			
			if (MAX_UPPER_BOUND / i < i)
			{
				continue;
			}

			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrime[j] = false;
			}
		}
	}

	return primeNumbers;
}

void ValidateUpperBound(int upperBound)
{
	if (upperBound > MAX_UPPER_BOUND)
	{
		throw std::invalid_argument("The upper limit shall not exceed 100000000");
	}
}
