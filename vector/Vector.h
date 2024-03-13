#pragma once
#include <vector>
#include <fstream>

std::vector<double> ParseDoublesToVector(std::istream& input);
void MultElementsByMin(std::vector<double>& vector);
