#pragma once

#include <array>
#include <string>
#include <optional>

using TripleMatrix = std::array<std::array<double, 3>, 3>;
using DoubleMatrix = std::array<std::array<double, 2>, 2>;

TripleMatrix ReadMatrixFromFile(const std::string& matrixFileName);
double GetTripleMatrixDeterminant(const TripleMatrix& matrix);
double GetDoubleMatrixDeterminant(const DoubleMatrix& matrix);
double GetMatrixMinor(size_t i, size_t j, const TripleMatrix& matrix);
std::optional<TripleMatrix> InvertMatrix(const TripleMatrix& matrix);
TripleMatrix ReadMatrixFromStream(std::istream& input);
void WriteMatrix(const TripleMatrix& matrix);