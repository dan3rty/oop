#include <iostream>
#include "../Replacer/Replacer.h"
#define CATCH_CONFIG_MAIN
#include "../catch2/catch.hpp"

TEST_CASE("String replacement with possible looping")
{
	std::string inputString = "мама мыла раму";
	std::string searchString = "ма";
	std::string replacementString = "мама";
	std::string expected = "мамамама мыла раму";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("String replacement with part repetition")
{
	std::string inputString = "12312312345";
	std::string searchString = "1231234";
	std::string replacementString = "4";
	std::string expected = "12345";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("Replacing an empty string")
{
	std::string inputString = "если бы бабушка была бы дедушкой";
	std::string searchString = "";
	std::string replacementString = "нет";
	std::string expected = "если бы бабушка была бы дедушкой";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}

TEST_CASE("Replace with an empty string")
{
	std::string inputString = "отсюда должно пропасть последнее слово";
	std::string searchString = "слово";
	std::string replacementString = "";
	std::string expected = "отсюда должно пропасть последнее ";
	std::string result = ReplaceString(inputString, searchString, replacementString);
	REQUIRE(result == expected);
}