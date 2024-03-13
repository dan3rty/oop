#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include "../Invert/Invert.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count" << std::endl
				  << "Usage: invert.exe <matrix file>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string matrixFileName = argv[1];
	try
	{
		TripleMatrix matrix = ReadMatrixFromFile(matrixFileName);

		if (auto invertedMatrix = InvertMatrix(matrix))
		{
			WriteMatrix(invertedMatrix.value());
		}
		else
		{
			std::cout << "Determinant is zero" << std::endl;
		}
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}