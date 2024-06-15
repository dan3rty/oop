#define CATCH_CONFIG_MAIN
#include "../FindMaxEx/FindMaxEx.hpp"
#include "../catch2/catch.hpp"

SCENARIO("find max element in an empty vector")
{
	GIVEN("an empty vector")
	{
		std::vector<int> vector;

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is not found")
				{
					REQUIRE_FALSE(found);
				}

				THEN("output variable is unchanged")
				{
					REQUIRE(result == 1337);
				}
			}
		}
	}
}

SCENARIO("find max element in the vector containing one element")
{
	GIVEN("a vector with one element")
	{
		int const element = 12;
		std::vector<int> vector{ element };

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("it equals to that single element")
				{
					REQUIRE(result == element);
				}
			}
		}
	}
}

SCENARIO("find max element in not empty vector with different value types")
{
	GIVEN("a vector of integers")
	{
		std::vector<int> vector{ 1, -3, 12, 9, 5, 12 };

		AND_GIVEN("output variable with a value")
		{
			int result = 1337;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](int l, int r) {
					return l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result == 12);
				}
			}
		}
	}

	GIVEN("a vector of doubles")
	{
		std::vector<double> vector{ 2.9, 12.67, -3.9, 2, 34.5, 9.3 };

		AND_GIVEN("output variable with a value")
		{
			double result = 1337.422;

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](double l, double r) {
					return std::abs(l - r) >= std::numeric_limits<double>::epsilon() && l < r;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result == 34.5);
				}
			}
		}
	}

	GIVEN("a vector of C-strings")
	{
		std::vector<char const*> vector{
			"Night, street, streetlight, drugstore",
			"A meaningless and dim light",
			"Live another quarter of a century",
			"It'll be like this. There's no end in sight",
		};

		AND_GIVEN("output variable with a value")
		{
			char const* result = "whatever";

			WHEN("finding max")
			{
				auto found = FindMaxEx(vector, result, [](char const* l, char const* r) {
					return std::strcmp(l, r) < 0;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(std::strcmp(result, "Night, street, streetlight, drugstore") == 0);
				}
			}
		}
	}

	GIVEN("a vector of structs")
	{
		struct Person
		{
			std::string name;
			int age;
		};

		std::vector<Person> vector = {
			{ "Brian Hopkin Jones", 27 },
			{ "Amy Jade Winehouse", 23 },
			{ "James Douglas Morrison", 19 },
		};

		AND_GIVEN("output variable with a value")
		{
			Person result{ "Somebody", 0 };

			WHEN("finding max by string")
			{
				auto found = FindMaxEx(vector, result, [](Person const& l, Person const& r) {
					return l.name > r.name;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result.name == "Amy Jade Winehouse");
					REQUIRE(result.age == 23);
				}
			}

			WHEN("finding max by integer")
			{
				auto found = FindMaxEx(vector, result, [](Person const& l, Person const& r) {
					return l.age < r.age;
				});

				THEN("it is found")
				{
					REQUIRE(found);
				}

				THEN("the value is correct")
				{
					REQUIRE(result.name == "Brian Hopkin Jones");
					REQUIRE(result.age == 27);
				}
			}
		}
	}
}