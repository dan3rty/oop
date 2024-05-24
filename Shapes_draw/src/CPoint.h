#pragma once

#define _USE_MATH_DEFINES
#include <cmath>

class CPoint
{
public:
	CPoint(double x, double y);

	double GetX() const;
	double GetY() const;

    //можно просто функцию сделать (GetDistance) ((Исправлено))

private:
	double m_x;
	double m_y;
};