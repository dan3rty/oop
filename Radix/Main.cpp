#include "Radix.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	int sourceRadix = std::stoi(argv[1]);
	int destRadix = std::stoi(argv[2]);
	std::string value = argv[3];

	bool error = false;
	int intValue = StringToInt(value, sourceRadix);

	std::string result = IntToString(intValue, destRadix);

	std::cout << result << "\n";

	return 0;
}
