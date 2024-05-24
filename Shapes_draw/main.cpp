#include "ShapeHandler.h"

int main()
{
	try
	{
		ShapeHandler processor(std::cin, std::cout);
		processor.ProcessShapes();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}