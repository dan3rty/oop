#include "CarControl.h"
#include <iostream>

int main()
{
	Car car;
	CarControl control(car, std::cin, std::cout);
	
	while (control.HandleCommand())
	{
		std::cout << std::endl;
	}

	return EXIT_SUCCESS;
}