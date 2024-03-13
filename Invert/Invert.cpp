#include "Invert.h"
#include <fstream>
#include <optional>
#include <iostream>
#include <iomanip>

TripleMatrix ReadMatrixFromFile(const std::string& inputFileName)
{
	std::ifstream matrixFile;
	matrixFile.open(inputFileName);
	if (!matrixFile.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}

	return ReadMatrixFromStream(matrixFile);
}

TripleMatrix ReadMatrixFromStream(std::istream& input)
{
	TripleMatrix matrix;
	double matrixElement;
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			if (!(input >> matrixElement))
			{
				throw std::invalid_argument("Invalid matrix");
			}
			matrix[i][j] = matrixElement;
		}
	}

	return matrix;
}

double GetTripleMatrixDeterminant(const TripleMatrix& matrix)
{
	double positiveDiagonal = matrix[0][0] * matrix[1][1] * matrix[2][2];
	double positiveTriangle1 = matrix[0][1] * matrix[1][2] * matrix[2][0];
	double positiveTriangle2 = matrix[1][0] * matrix[2][1] * matrix[0][2];

	double negativeDiagonal = matrix[0][2] * matrix[1][1] * matrix[2][0];
	double negativeTriangle1 = matrix[0][1] * matrix[1][0] * matrix[2][2];
	double negativeTriangle2 = matrix[0][0] * matrix[1][2] * matrix[2][1];

	return positiveDiagonal + positiveTriangle1 + positiveTriangle2
		- negativeDiagonal - negativeTriangle1 - negativeTriangle2;
}

double GetDoubleMatrixDeterminant(const DoubleMatrix& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

double GetMatrixMinor(size_t i, size_t j, const TripleMatrix& matrix)
{
	DoubleMatrix minorMatrix{};
	int minorRow = 0;
	for (size_t row = 0; row < 3; ++row)
	{
		if (row == i)
			continue;
		int minorColumn = 0;
		for (size_t col = 0; col < 3; ++col)
		{
			if (col == j)
				continue;
			minorMatrix[minorRow][minorColumn] = matrix[row][col];
			minorColumn++;
		}
		minorRow++;
	}

	return GetDoubleMatrixDeterminant(minorMatrix);
}


std::optional<TripleMatrix> InvertMatrix(const TripleMatrix& matrix)
{
	const double matrixDeterminant = GetTripleMatrixDeterminant(matrix);
	if (matrixDeterminant == 0)
	{
		//данная функция ничего не должна выводить (исправлено)
		return std::nullopt;
	}

	TripleMatrix invertedMatrix{};
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			double degree = ((i + j) % 2 == 0) ? 1.0 : -1.0;
			invertedMatrix[j][i] = GetMatrixMinor(i, j, matrix) / matrixDeterminant;
			invertedMatrix[j][i] *= degree;
		}
	}

	return invertedMatrix;
}

void WriteMatrix(const TripleMatrix& matrix)
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}