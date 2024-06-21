#define CATCH_CONFIG_MAIN
#include "../UrlParser/UrlParser.h"
#include "../catch2/catch.hpp"

TEST_CASE("URL parsing works correctly")
{
	SECTION("protocol is parsed correctly")
	{
		SECTION("valid protocol returns enum value")
		{
			REQUIRE(ParseProtocol("http") == Protocol::HTTP);
			REQUIRE(ParseProtocol("https") == Protocol::HTTPS);
			REQUIRE(ParseProtocol("ftp") == Protocol::FTP);
		}

		SECTION("empty or invalid protocol results in an exception")
		{
			REQUIRE_THROWS_AS(ParseProtocol(""), std::invalid_argument);
			REQUIRE_THROWS_AS(ParseProtocol("telnet"), std::invalid_argument);
		}
	}

	SECTION("host is parsed correctly")
	{
		SECTION("valid host returns the same value")
		{
			REQUIRE(ParseHost("github.com") == "github.com");
		}

		SECTION("invalid empty host results in an exception")
		{
			REQUIRE_THROWS_AS(ParseHost(""), std::invalid_argument);
		}
	}

	SECTION("port parsing works correctly")
	{
		SECTION("valid port is parsed correctly")
		{
			REQUIRE(ParsePort("42", Protocol::HTTP) == 42);
		}

		SECTION("empty port results in default value for specific protocol")
		{
			REQUIRE(ParsePort("", Protocol::HTTP) == 80);
			REQUIRE(ParsePort("", Protocol::HTTPS) == 443);
			REQUIRE(ParsePort("", Protocol::FTP) == 21);
		}

		SECTION("exceeding port value results in an error")
		{
			//MIN_PORT и MAX_PORT лучше скрывать (объ€вить в cpp и объ€вить в тестах)
			REQUIRE_THROWS_AS(ParsePort(std::to_string(MIN_PORT - 1), Protocol::HTTP), std::invalid_argument);
			REQUIRE_THROWS_AS(ParsePort(std::to_string(MAX_PORT + 1), Protocol::HTTP), std::invalid_argument);
		}

		SECTION("invalid port format results in an exception")
		{
			REQUIRE_THROWS_AS(ParsePort("not a port", Protocol::HTTP), std::invalid_argument);
		}
	}

	SECTION("overall URL parsing works correctly")
	{
		SECTION("valid URL is parsed correctly")
		{
			const std::string url = "https://github.com/dan3rty";
			auto const info = ParseURL(url);

			REQUIRE(info.url == url);
			REQUIRE(info.protocol == Protocol::HTTPS);
			REQUIRE(info.host == "github.com");
			REQUIRE(info.port == 443);
			REQUIRE(info.document == "dan3rty");
		}

		SECTION("empty document does not result in an error not depending on the slash at the end")
		{
			const std::string url = "https://github.com";
			auto const info = ParseURL(url);
			REQUIRE(info.document.empty());

			const std::string urlWithSlash = "https://github.com/";
			auto const infoWithSlash = ParseURL(urlWithSlash);
			REQUIRE(infoWithSlash.document.empty());
		}

		SECTION("invalid URL results in an exception")
		{
			const std::string url = "hello there";
			REQUIRE_THROWS_AS(ParseURL(url), std::invalid_argument);
		}

		SECTION("only a substring is valid URL")
		{
			const std::string url = "hhttps://github.com/dan3rty";
			REQUIRE_THROWS_AS(ParseURL(url), std::invalid_argument);
		}
	}
}

TEST_CASE("printing out URL information works correctly")
{
	std::stringstream output;
	URLInfo info;
	info.url = "https://github.com/dan3rty";
	info.protocol = Protocol::HTTPS;
	info.host = "github.com";
	info.port = 443;
	info.document = "dan3rty";
	PrintURLInfo(output, info);

	REQUIRE(output.str() == "https://github.com/dan3rty\nHOST: github.com\nPORT: 443\nDOC: dan3rty\n");
}

TEST_CASE("stream processing works correctly")
{
	SECTION("valid URLs are printed as expected")
	{
		std::stringstream input("https://github.com/dan3rty");
		std::stringstream output;
		ProcessURLs(input, output);

		REQUIRE(output.str() == "https://github.com/dan3rty\nHOST: github.com\nPORT: 443\nDOC: dan3rty\n");
	}

	SECTION("an error message is printed or invalid URLs")
	{
		std::stringstream input("hello there");
		std::stringstream output;
		ProcessURLs(input, output);

		REQUIRE(output.str() == "URL parsing error: invalid URL\n");
	}
}