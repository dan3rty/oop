#include <iostream>
#include <string>
#include "Radix.h"

constexpr const int DECIMAL = 10;

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

//нет смысла в optional оборачивать(исправлено)
Args ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument("Usage: radix.exe <source notation> <destination notation> <value>");
		//не дойдёт до сюда(исправлено)
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];
	return args;
}

int main(int argc, char* argv[])
{
	try
	{
		//переменные с маленькой (исправлено)
		auto args = ParseArgs(argc, argv);
		int sourceNotation = StringToInt(args.sourceNotation, DECIMAL);
		int destinationNotation = StringToInt(args.destinationNotation, DECIMAL);
		std::cout << ChangeNumberNotation(sourceNotation, destinationNotation, args.value) << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}