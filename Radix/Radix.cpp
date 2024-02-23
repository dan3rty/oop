#include <cmath>
#include <exception>
#include <format>
#include <iostream>
#include <optional>
#include <string>
#include "Radix.h"

constexpr const int CHAR_OFFSET = 10;

struct Args
{
	std::string sourceNotation;
	std::string destinationNotation;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		throw std::invalid_argument("Usage: radix.exe <source notation> <destination notation> <value>");
		return std::nullopt;
	}
	Args args;
	args.sourceNotation = argv[1];
	args.destinationNotation = argv[2];
	args.value = argv[3];
	return args;
}

int StringToInt(const std::string& str, int radix)
{
	int result = 0;
	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
	}
	for (size_t i = isNegative; i < str.length(); i++)
	{
		int digit = CharToInt(str[i]);
		if (digit >= radix)
		{
			throw std::invalid_argument(std::format("The digit \"{}\" is not supported by the number system \"{}\"", str[i], radix));
		}
		result = isNegative ? result * radix - digit : result * radix + digit;
	}
	return result;
}

int CharToInt(const char& symbol)
{
	if (symbol >= '0' && symbol <= '9')
	{
		return symbol - '0';
	}
	else if (symbol >= 'A' && symbol <= 'Z')
	{
		return symbol - 'A' + CHAR_OFFSET;
	}
	else
	{
		throw std::invalid_argument(std::format("Unkown symbol: {}", symbol));
	}
}

std::string IntToString(int n, int radix)
{
	if (n == 0)
	{
		return "0";
	}
	std::string result = "";
	bool isNegative = false;
	if (n < 0)
	{
		isNegative = true;
		n *= -1;
	}
	while (n > 0)
	{
		int digit = n % radix;
		char c;
		if (digit < 10)
		{
			c = '0' + digit;
		}
		else
		{
			c = 'A' + digit - 10;	
		}
		result = c + result;
		n /= radix;
	}
	result = isNegative ? '-' + result : result;
	return result;
}

std::string numberConversion(const std::string& sourceNotation, const std::string& destinationNotation, const std::string& value)
{
	return IntToString(StringToInt(value, StringToInt(sourceNotation, 10)), StringToInt(destinationNotation, 10));
}
