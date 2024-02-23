#include <string>
#include <fstream>
#include "Replacer.h"

std::string ReplaceString(const std::string& subject,
	const std::string& searchString, const std::string& replacementString)
{
	if (searchString.empty())
	{
		return subject;
	}

	size_t pos = 0;
	size_t lastPos = 0;
	std::string result;

	while (pos != std::string::npos)
	{
		pos = subject.find(searchString, pos);
		result.append(subject, lastPos, pos - lastPos);
		if (pos != std::string::npos)
		{
			result.append(replacementString);
			pos += searchString.length();
			lastPos = pos;
		}
	}

	return result;
}

void CopyStreamWithReplacement(std::istream& input, std::ostream& output,
	const std::string& searchString, const std::string& replacementString)
{
	std::string line;

	while (std::getline(input, line))
	{
		output << ReplaceString(line, searchString, replacementString) << std::endl;
	}
	if (!input.eof())
	{
		throw std::runtime_error("Failed with reading the input file");
	}
}

void CopyFileWithReplacement(const std::string& inputFileName, const std::string& outputFileName,
	const std::string& searchString, const std::string& replaceString)
{
	std::ifstream inputFile(inputFileName);
	std::ofstream outputFile(outputFileName);

	if (!inputFile.is_open())
	{
		throw std::invalid_argument("Failed to open input file");
	}

	if (!outputFile.is_open())
	{
		throw std::invalid_argument("Failed to open output file");
	}

	CopyStreamWithReplacement(inputFile, outputFile, searchString, replaceString);

	if (!outputFile.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
}