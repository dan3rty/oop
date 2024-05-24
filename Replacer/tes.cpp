#include <iostream>
#include <string>

int SwapByte(int num)
{
	if (num < 0 || num > 255)
	{
		throw std::invalid_argument("Invalid arguments. Enter num 0 - 255");
	}

	num = ((num & 0b1111) << 4) | ((num & 0b11110000) >> 4);
	num = ((num & 0b110011) << 2) | ((num & 0b11001100) >> 2);
	num = ((num & 0b01010101) << 1) | ((num & 0b10101010) >> 1);
	
	return num;
}

int ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		throw std::invalid_argument("Invalid arguments count.\n Usage: flipByte.exe <num>.");
	}

	int num = std::stoi(argv[1]);

	return num;
}

int main(int argc, char* argv[])
{
	try
	{
		auto num = ParseArgs(argc, argv);
		std::cout << SwapByte(num) << std::endl;
	}
	catch (const std::exception& exception)
	{
		std::cout << exception.what()  << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}