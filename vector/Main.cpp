#include "Vector.h"
#include <iostream>
#include <algorithm>


int main()
{
	std::vector<double> inputData;

	inputData = ParseDoublesToVector(std::cin);

	MultElementsByMin(inputData);

	std::ranges::sort(inputData);

	std::ranges::copy(inputData, std::ostream_iterator<double>(std::cout, " "));

	return EXIT_SUCCESS;
}