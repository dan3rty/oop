#include "Utils.h"

void PrintColor(std::ostream& output, uint32_t color)
{
	output << '#'
		   << std::hex << std::setw(6) << std::setfill('0')
		   << color;
}

double GetDistance(const CPoint& p1, const CPoint& p2)
{
    auto x = (p2.GetX() - p1.GetX()) * (p2.GetX() - p1.GetX());
    auto y = (p2.GetY() - p1.GetY()) * (p2.GetY() - p1.GetY());

    return std::sqrt(x + y);
}