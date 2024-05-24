#define CATCH_CONFIG_MAIN
#include "../Shapes/CCircle.h"
#include "../Shapes/CLineSegment.h"
#include "../Shapes/CRectangle.h"
#include "../Shapes/CTriangle.h"
#include "../Shapes/ShapeHandler.h"
#include "../catch2/catch.hpp"

bool ApproximatelyEquals(double a, double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

TEST_CASE("Operations with shapes")
{
	uint32_t outlineColor = 0xF62681;
	uint32_t fillColor = 0xFF00FF;

	SECTION("Operations with points")
	{

		SECTION("Calculate distance between two points")
		{
			CPoint p1(3, 4);
			CPoint p2(0, 0);

			SECTION("Calculate distance between same points")
			{
				auto distance = CPoint::GetDistance(p1, p1);
				REQUIRE(ApproximatelyEquals(distance, 0));
			}

			SECTION("Calculate distance between different points")
			{
				auto distance = CPoint::GetDistance(p1, p2);
				REQUIRE(ApproximatelyEquals(distance, 5));
			}
		}
	}

	SECTION("Operations with line segment")
	{
		CPoint start(0, 1);
		CPoint end(2, 7);
		CLineSegment line(start, end, outlineColor);

		SECTION("Calculate line perimeter")
		{
			double expected = CPoint::GetDistance(start, end);
			REQUIRE(ApproximatelyEquals(line.GetPerimeter(), expected));
		}
	}

	SECTION("Operations with circle")
	{
		CPoint center(5, 5);
		double radius = 3;
		CCircle circle(center, radius, outlineColor, fillColor);

		SECTION("Calculate circle area")
		{
			double expected = M_PI * radius * radius;
			REQUIRE(ApproximatelyEquals(circle.GetArea(), expected));
		}

		SECTION("Calculate circle perimeter")
		{
			double expected = 2 * M_PI * radius;
			REQUIRE(ApproximatelyEquals(circle.GetPerimeter(), expected));
		}
	}

	SECTION("Operations with rectangle")
	{
		CPoint leftTop(11, 12);
		CPoint rightBottom(14, 5);
		CRectangle rectangle(leftTop, rightBottom, outlineColor, fillColor);

		SECTION("Calculate width and height")
		{
			double expectedWidth = rightBottom.GetX() - leftTop.GetX();
			REQUIRE(ApproximatelyEquals(rectangle.GetWidth(), expectedWidth));

			double expectedHeight = leftTop.GetY() - rightBottom.GetY();
			REQUIRE(ApproximatelyEquals(rectangle.GetHeight(), expectedHeight));
		}

		SECTION("Calculate rectangle area")
		{
			double expected = (rightBottom.GetX() - leftTop.GetX()) * (leftTop.GetY() - rightBottom.GetY());
			REQUIRE(ApproximatelyEquals(rectangle.GetArea(), expected));
		}

		SECTION("Calculate rectangle perimeter")
		{
			double expected = 2 * ((rightBottom.GetX() - leftTop.GetX()) + (leftTop.GetY() - rightBottom.GetY()));
			REQUIRE(ApproximatelyEquals(rectangle.GetPerimeter(), expected));
		}
	}

	SECTION("Operations with triangle")
	{
		CPoint vertex1(0, 0);
		CPoint vertex2(2, 0);
		CPoint vertex3(2, 3);
		CTriangle triangle(vertex1, vertex2, vertex3, outlineColor, fillColor);

		SECTION("Calculate triangle area")
		{
			double expected = CPoint::GetDistance(vertex1, vertex2) * CPoint::GetDistance(vertex2, vertex3) / 2;
			REQUIRE(ApproximatelyEquals(triangle.GetArea(), expected));
		}

		SECTION("Calculate triangle perimeter")
		{
			double expected = CPoint::GetDistance(vertex1, vertex2) + CPoint::GetDistance(vertex2, vertex3) + CPoint::GetDistance(vertex3, vertex1);
			REQUIRE(ApproximatelyEquals(triangle.GetPerimeter(), expected));
		}
	}
}

TEST_CASE("Send commands to handler")
{
	std::istringstream input;
	std::ostringstream output;
	ShapeHandler handler(input, output);

	input.str("circle 100 30 20 FF00FF FF00FF\ntriangle 300 300 310 200 210 400 FFC0CB FFC0CB\n");
	handler.ProcessShapes();
	const std::string result = "\n[Largest area shape]\n"
							   "TRIANGLE\n"
							   "  vertex1: (300.00, 300.00)\n"
							   "  vertex2: (310.00, 200.00)\n"
							   "  vertex3: (210.00, 400.00)\n"
							   "  outline: #ffc0cb\n"
							   "  fill: #ffc0cb\n"
							   "  area: 4000.00\n"
							   "  perimeter: 458.64\n"
							   "\n[Smallest perimeter shape]\n"
							   "CIRCLE\n"
							   "  center: (100.00, 30.00)\n"
							   "  radius: 20.00\n"
							   "  outline: #ff00ff\n"
							   "  fill: #ff00ff\n"
							   "  area: 1256.64\n"
							   "  perimeter: 125.66\n";
	REQUIRE(result == output.str());
}