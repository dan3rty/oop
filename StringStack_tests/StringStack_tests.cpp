#include "../StringStack/CStringStack.h"
#include "../StringStack/CStringStackUnderflowError.h"
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

SCENARIO("creating a stack")
{
	GIVEN("nothing")
	{
		WHEN("stack is created")
		{
			CStringStack stack;

			THEN("it's empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}
		}
	}

	GIVEN("another empty stack")
	{
		CStringStack original;

		WHEN("copying")
		{
			CStringStack stack = original;

			THEN("it is empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}

			THEN("original is still empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}

			WHEN("modifying the original doesn't affect the copy")
			{
				original.Push("Balderdash");

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.IsEmpty());
				}
			}
		}

		WHEN("moving to another stack")
		{
			CStringStack stack = std::move(original);

			THEN("it is empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}

			THEN("original is still empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}

	GIVEN("another stack with one element")
	{
		CStringStack original;
		std::string const element = "Doodle";
		original.Push(element);

		WHEN("copying")
		{
			CStringStack stack = original;

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("original is still not empty")
			{
				REQUIRE_FALSE(original.IsEmpty());
			}

			THEN("original size equals 1")
			{
				REQUIRE(original.GetSize() == 1);
			}

			THEN("the element matches")
			{
				REQUIRE(stack.Top() == element);
			}

			WHEN("modifying the original")
			{
				original.Pop();

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.Top() == element);
				}
			}
		}

		WHEN("moving")
		{
			CStringStack stack = std::move(original);

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("top element matches the original one")
			{
				REQUIRE(stack.Top() == element);
			}

			THEN("original becomes empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}

	GIVEN("another stack with several elements")
	{
		CStringStack original;
		std::string const element1 = "You shouldn't";
		std::string const element2 = "have read";
		std::string const element3 = "that";
		original.Push(element1);
		original.Push(element2);
		original.Push(element3);

		WHEN("copying")
		{
			CStringStack stack = original;

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 3")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("original is still not empty")
			{
				REQUIRE_FALSE(original.IsEmpty());
			}

			THEN("original size equals 3")
			{
				REQUIRE(original.GetSize() == 3);
			}

			THEN("the elements match")
			{
				REQUIRE(stack.Top() == element3);
				stack.Pop();
				REQUIRE(stack.Top() == element2);
				stack.Pop();
				REQUIRE(stack.Top() == element1);
			}

			WHEN("modifying the original")
			{
				original.Pop();

				THEN("it doesn't affect the copy")
				{
					REQUIRE(stack.Top() == element3);
				}
			}
		}

		WHEN("moving")
		{
			CStringStack stack = std::move(original);

			THEN("it is not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("elements match the original ones")
			{
				REQUIRE(stack.Top() == element3);
				stack.Pop();
				REQUIRE(stack.Top() == element2);
				stack.Pop();
				REQUIRE(stack.Top() == element1);
			}

			THEN("original becomes empty")
			{
				REQUIRE(original.IsEmpty());
			}

			THEN("original size equals 0")
			{
				REQUIRE(original.GetSize() == 0);
			}
		}
	}
}

SCENARIO("assigning a stack")
{
	GIVEN("source stack with several elements")
	{
		CStringStack source;
		std::string const sourceElement1 = "You shouldn't have";
		std::string const sourceElement2 = "read that";
		source.Push(sourceElement1);
		source.Push(sourceElement2);

		GIVEN("empty stack")
		{
			CStringStack stack;

			WHEN("copying")
			{
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}

		GIVEN("stack with one element")
		{
			CStringStack stack;
			std::string const element = "Baltika 9";
			stack.Push(element);

			WHEN("copying")
			{
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}

		GIVEN("stack with several elements")
		{
			CStringStack stack;
			std::string const element1 = "while I'm writing these tests";
			std::string const element2 = "there are children starving in africa";
			std::string const element3 = "but the tests are much more important";
			stack.Push(element1);
			stack.Push(element2);
			stack.Push(element3);

			WHEN("copying")
			{
				stack = source;

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source is still not empty")
				{
					REQUIRE_FALSE(source.IsEmpty());
				}

				THEN("source size equals 2")
				{
					REQUIRE(source.GetSize() == 2);
				}

				THEN("the elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				WHEN("modifying the source")
				{
					source.Pop();

					THEN("it doesn't affect the copy")
					{
						REQUIRE(stack.Top() == sourceElement2);
					}
				}
			}

			WHEN("moving")
			{
				stack = std::move(source);

				THEN("it is not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 2")
				{
					REQUIRE(stack.GetSize() == 2);
				}

				THEN("source elements match")
				{
					REQUIRE(stack.Top() == sourceElement2);
					stack.Pop();
					REQUIRE(stack.Top() == sourceElement1);
				}

				THEN("source stack becomes empty")
				{
					REQUIRE(source.IsEmpty());
				}

				THEN("source size equals 0")
				{
					REQUIRE(source.GetSize() == 0);
				}
			}
		}

		WHEN("copy-assigning stack to itself")
		{
			source = source;

			THEN("it doesn't change")
			{
				REQUIRE_FALSE(source.IsEmpty());
				REQUIRE(source.GetSize() == 2);

				REQUIRE(source.Top() == sourceElement2);
				source.Pop();
				REQUIRE(source.Top() == sourceElement1);
			}
		}

		WHEN("move-assigning stack to itself")
		{
			source = std::move(source);

			THEN("it doesn't change")
			{
				REQUIRE_FALSE(source.IsEmpty());
				REQUIRE(source.GetSize() == 2);

				REQUIRE(source.Top() == sourceElement2);
				source.Pop();
				REQUIRE(source.Top() == sourceElement1);
			}
		}
	}
}

SCENARIO("getting top element from the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("getting the top element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stack.Top(), CStringStackUnderflowError);
			}
		}
	}

	GIVEN("stack with one element")
	{
		CStringStack stack;
		std::string const element = "kill me.";
		stack.Push(element);

		WHEN("getting the top element")
		{
			THEN("it returns the added string")
			{
				REQUIRE(stack.Top() == element);
			}
		}
	}

	GIVEN("stack with several elements")
	{
		CStringStack stack;
		std::string const lastElement = "A little bird sings in the woods";
		stack.Push("Fish swimming in the pond");
		stack.Push("And Hitler lives in Antarctica");
		stack.Push(lastElement);

		WHEN("getting the top element")
		{
			THEN("it returns the added string")
			{
				REQUIRE(stack.Top() == lastElement);
			}
		}
	}
}

SCENARIO("adding elements to the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("pushing one element")
		{
			std::string const element = "the sun is shining brightly";
			stack.Push(element);

			THEN("it's not empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 1")
			{
				REQUIRE(stack.GetSize() == 1);
			}

			THEN("top element matches")
			{
				REQUIRE(stack.Top() == element);
			}

			WHEN("pushing more elements")
			{
				std::string const element1 = "one day mankind will be extinct.";
				std::string const element2 = "you shouldn't be drinking acid";
				stack.Push(element1);
				stack.Push(element2);

				THEN("it's not empty")
				{
					REQUIRE_FALSE(stack.IsEmpty());
				}

				THEN("size equals 3")
				{
					REQUIRE(stack.GetSize() == 3);
				}

				THEN("top element matches the last one")
				{
					REQUIRE(stack.Top() == element2);
				}
			}
		}
	}
}

SCENARIO("removing elements from the stack")
{
	GIVEN("empty stack")
	{
		CStringStack stack;

		WHEN("removing an element")
		{
			THEN("it throws an exception")
			{
				REQUIRE_THROWS_AS(stack.Pop(), CStringStackUnderflowError);
			}
		}
	}

	GIVEN("stack with one element")
	{
		CStringStack stack;
		stack.Push("the most painless death is at the center of a nuclear explosion");

		WHEN("removing an element")
		{
			stack.Pop();

			THEN("it becomes empty")
			{
				REQUIRE(stack.IsEmpty());
			}

			THEN("size equals 0")
			{
				REQUIRE(stack.GetSize() == 0);
			}

			WHEN("removing an element again")
			{
				THEN("it throws an exception")
				{
					REQUIRE_THROWS_AS(stack.Pop(), CStringStackUnderflowError);
				}
			}
		}
	}

	GIVEN("stack with several elements")
	{
		CStringStack stack;
		stack.Push("A bird sings in the forest");
		stack.Push("A fish swims in a pond");
		std::string const aboveLastElement = "A scarab beetle sleeps in a pyramid";
		stack.Push(aboveLastElement);
		stack.Push("And Hitler lives in Antarctica");

		WHEN("removing an element")
		{
			stack.Pop();

			THEN("it doesn't become empty")
			{
				REQUIRE_FALSE(stack.IsEmpty());
			}

			THEN("size equals 3")
			{
				REQUIRE(stack.GetSize() == 3);
			}

			THEN("top element is the above last one")
			{
				REQUIRE(stack.Top() == aboveLastElement);
			}
		}
	}
}