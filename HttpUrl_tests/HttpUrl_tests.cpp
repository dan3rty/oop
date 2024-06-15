#define CATCH_CONFIG_MAIN
#include "../HttpUrl/CHttpUrl.h"
#include "../catch2/catch.hpp"

TEST_CASE("constructing an URL")
{
	std::string const sourceUrl = "http://github.com/dan3rty";
	std::string const sourceUrlWPort = "http://github.com:80/dan3rty";
	std::string const sourceUrlWODocument = "http://github.com";
	std::string const sourceUrlWMixedCaseProtocol = "hTTp://github.com/dan3rty";
	std::string const sourceUrlWMinPort = "hTTp://github.com:1/dan3rty";
	std::string const sourceUrlWMaxPort = "hTTp://github.com:65535/dan3rty";

	std::string const domain = "github.com";
	std::string const document = "/dan3rty";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;
	CHttpUrl::Port const minPort = 1;
	CHttpUrl::Port const maxPort = 65535;

	SECTION("with all fields")
	{
		SECTION("with not empty document")
		{
			CHttpUrl url(domain, document, protocol, port);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == protocol);
			REQUIRE(url.GetPort() == port);
		}

		SECTION("with empty document")
		{
			CHttpUrl url(domain, "", protocol, port);

			REQUIRE(url.GetDocument() == "/");
		}

		SECTION("with document without leading slash")
		{
			CHttpUrl url(domain, "wut", protocol, port);

			REQUIRE(url.GetDocument() == "/wut");
		}
	}

	SECTION("without port")
	{
		SECTION("with https protocol")
		{
			CHttpUrl url(domain, document, CHttpUrl::Protocol::HTTPS);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == CHttpUrl::Protocol::HTTPS);
			REQUIRE(url.GetPort() == 443);
		}

		SECTION("with not empty document")
		{
			CHttpUrl url(domain, document, protocol);

			REQUIRE(url.GetDomain() == domain);
			REQUIRE(url.GetDocument() == document);
			REQUIRE(url.GetProtocol() == protocol);
			REQUIRE(url.GetPort() == port);
		}

		SECTION("with empty document")
		{
			CHttpUrl url(domain, "", protocol);

			REQUIRE(url.GetDocument() == "/");
		}

		SECTION("with document without leading slash")
		{
			CHttpUrl url(domain, "wut", protocol);

			REQUIRE(url.GetDocument() == "/wut");
		}
	}

	SECTION("from a string")
	{
		SECTION("valid URL")
		{
			SECTION("with explicit port")
			{
				CHttpUrl url = sourceUrlWPort;

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == document);
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}

			SECTION("without port")
			{
				CHttpUrl url = sourceUrl;

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == document);
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}

			SECTION("without document")
			{
				CHttpUrl url = sourceUrlWODocument;

				REQUIRE(url.GetDomain() == domain);
				REQUIRE(url.GetDocument() == "/");
				REQUIRE(url.GetProtocol() == protocol);
				REQUIRE(url.GetPort() == port);
			}

			SECTION("protocol parsing is case-insensitive")
			{
				CHttpUrl url = sourceUrlWMixedCaseProtocol;

				REQUIRE(url.GetProtocol() == protocol);
			}

			SECTION("borderline port is parsed correctly")
			{
				CHttpUrl urlMin = sourceUrlWMinPort;
				REQUIRE(urlMin.GetPort() == minPort);

				CHttpUrl urlMax = sourceUrlWMaxPort;
				REQUIRE(urlMax.GetPort() == maxPort);
			}
		}

		SECTION("invalid URL")
		{
			SECTION("overall")
			{
				REQUIRE_THROWS_AS(CHttpUrl("wut"), CUrlParsingError);
			}

			SECTION("with empty domain")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http:///dan3rty"), CUrlParsingError);
			}

			SECTION("with invalid port")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:alksjd/dan3rty"), CUrlParsingError);
			}

			SECTION("with out-of-range port")
			{
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:-1/dan3rty"), CUrlParsingError);
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:0/dan3rty"), CUrlParsingError);
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:100000000000000000/dan3rty"), CUrlParsingError);
				REQUIRE_THROWS_AS(CHttpUrl("http://github.com:65536/dan3rty"), CUrlParsingError);
			}

			SECTION("valid withing a string")
			{
				REQUIRE_THROWS_AS(CHttpUrl("whatever https://github.com/sneed "), CUrlParsingError);
			}
		}
	}
}

TEST_CASE("building a string URL")
{
	std::string const sourceUrl = "http://github.com/dan3rty";
	std::string const domain = "github.com";
	std::string const document = "/dan3rty";
	CHttpUrl::Protocol const protocol = CHttpUrl::Protocol::HTTP;
	CHttpUrl::Port const port = 80;

	std::string const sourceUrlWCustomPort = "http://github.com:12/dan3rty";
	CHttpUrl::Port const customPort = 12;

	std::string const sourceUrlWODocument = "http://github.com/";

	SECTION("with standard port")
	{
		CHttpUrl url(domain, document, protocol, port);

		REQUIRE(url.GetUrl() == sourceUrl);
	}

	SECTION("with non-standard port")
	{
		CHttpUrl url(domain, document, protocol, customPort);

		REQUIRE(url.GetUrl() == sourceUrlWCustomPort);
	}

	SECTION("with empty document")
	{
		CHttpUrl url(domain, "", protocol);

		REQUIRE(url.GetUrl() == sourceUrlWODocument);
	}
}

TEST_CASE("converting protocol to string")
{
	REQUIRE(CHttpUrl::ProtocolToString(CHttpUrl::Protocol::HTTP) == "http");
	REQUIRE(CHttpUrl::ProtocolToString(CHttpUrl::Protocol::HTTPS) == "https");
}
