#include <vector>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <execution>

std::vector<double> ParseDoublesToVector(std::istream& input)
{
    std::vector<double> v(std::istream_iterator<double>(input), (std::istream_iterator<double>()));

	return v;
};

void MultElementsByMin(std::vector<double>& vector)
{
	if (vector.empty())
	{
		return;
	}

	double min_element = *std::min_element(
		std::execution::par,
		vector.begin(), 
		vector.end()
	);

	std::transform(
		std::execution::par,
		vector.begin(), 
		vector.end(), 
		vector.begin(), 
		[min_element](double element) {return element * min_element;}
	);
}
