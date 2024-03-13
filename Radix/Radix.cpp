#include <cmath>
#include <exception>
#include <format>
#include <iostream>
#include <string>
#include "Radix.h"

constexpr const int DECIMAL = 10;
constexpr const int MIN_RADIX = 2;
constexpr const int MAX_RADIX = 36;

int StringToInt(const std::string& str, int radix)
{
	int result = 0;
	//проверка на пустую строку(исправлено)
	if (str.empty())
	{
		return result;
	}
	bool isNegative = str[0] == '-';

	//преобразование bool в size_t(исправлено)
	for (size_t i = isNegative ? 1 : 0; i < str.length(); i++)
	{
		int digit = CharToInt(str[i]);

		if (IsSumOverflowed(result, digit, radix))
		{
			throw std::invalid_argument("Overflow occured");
		}

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
		return symbol - 'A' + DECIMAL;
	}
	throw std::invalid_argument(std::format("Not supported symbol: {}", symbol));
}

//название функции неправильное, ещё и произведение Overflowed => Overflown
bool IsSumOverflowed(int a, int b, int radix)
{
	bool moreThanMaxInt = a > 0 && b > INT_MAX - a * radix;
	bool lessThanMinInt = a < 0 && b > a * radix - INT_MIN;
	return moreThanMaxInt || lessThanMinInt;
}

std::string IntToString(int n, int radix)
{
	//убрать костыль с 0
	if (n == 0)
	{
		return "0";
	}
	std::string result;
	bool isNegative = n < 0;
	while (n != 0)//как сделать так, чтобы 0 обработался
	{	
		int digit = n % radix;
		result = IntToChar(digit) + result;
		n /= radix;
	}
	result = isNegative ? '-' + result : result;
	return result;
}

//не надо сюда подавать отрицательные числа
char IntToChar(int n)
{
	n = std::abs(n);
	if (n < DECIMAL)
	{
		return static_cast<char>('0' + n);
	}
	else
	{
		return static_cast<char>('A' + n - DECIMAL);
	}
}

std::string ChangeNumberNotation(int sourceNotation, int destinationNotation, const std::string& value)
{
	if (!IsNotationsValid(sourceNotation, destinationNotation))
	{
		throw std::invalid_argument(std::format("Notations should be between {} and {}", MIN_RADIX, MAX_RADIX));
	}
	return IntToString(StringToInt(value, sourceNotation), destinationNotation);
}

bool IsNotationsValid(int sourceNotation, int destinationNotation)
{
	return IsNotationValid(sourceNotation) && IsNotationValid(destinationNotation);
}

bool IsNotationValid(int notation)
{
	return MIN_RADIX <= notation && notation <= MAX_RADIX;
}