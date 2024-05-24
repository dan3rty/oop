#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "CCircle.h"
#include "CLineSegment.h"
#include "CRectangle.h"
#include "CTriangle.h"
#include "ShapeHandler.h"
#include <cstdint>

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
				auto distance = GetDistance(p1, p1);
				REQUIRE(ApproximatelyEquals(distance, 0));
			}

			SECTION("Calculate distance between different points")
			{
				auto distance = GetDistance(p1, p2);
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
			double expected = GetDistance(start, end);
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
			double expected = GetDistance(vertex1, vertex2) * GetDistance(vertex2, vertex3) / 2;
			REQUIRE(ApproximatelyEquals(triangle.GetArea(), expected));
		}

		SECTION("Calculate triangle perimeter")
		{
			double expected = GetDistance(vertex1, vertex2) + GetDistance(vertex2, vertex3) + GetDistance(vertex3, vertex1);
			REQUIRE(ApproximatelyEquals(triangle.GetPerimeter(), expected));
		}
	}
}
//рисовашку тоже потестить быыыыыыыы
