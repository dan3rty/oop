#include "../Replacer/Replacer.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>

struct Args
{
	std::string inputFileName;
	std::string outputFileName;
	std::string searchString;
	std::string replaceString;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::invalid_argument("Usage: replacer.exe <inputFile> <outputFile> <searchString> <replacementString>");
		return std::nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		auto Args = ParseArgs(argc, argv);
		CopyFileWithReplacement(Args->inputFileName, Args->outputFileName, Args->searchString, Args->replaceString);
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
