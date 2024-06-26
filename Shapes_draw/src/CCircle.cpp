#include "CCircle.h"
#include <cmath>

CCircle::CCircle(CPoint center, double radius, uint32_t outlineColor, uint32_t fillColor)
	: m_center(center)
	, m_radius(radius)
	, CSolidShape(outlineColor, fillColor)
{
}

double CCircle::GetArea() const
{
	return M_PI * m_radius * m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

std::string CCircle::ToString() const
{
	std::stringstream result;
	result << std::fixed << std::setprecision(2)
		   << "CIRCLE\n"
		   << "  center: (" << m_center.GetX() << ", " << m_center.GetY() << ")\n"
		   << "  radius: " << m_radius << "\n"
		   << "  outline: ";
	PrintColor(result, GetOutlineColor());
	result << "\n  fill: ";
	PrintColor(result, GetFillColor());
	result << '\n';

	return result.str();
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}


void CCircle::Draw(ICanvas& canvas) const
{
    canvas.DrawCircle(m_center, m_radius, GetOutlineColor(), GetFillColor());
}
