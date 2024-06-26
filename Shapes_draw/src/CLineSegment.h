#pragma once

#include "CPoint.h"
#include "Utils.h"
#include "CShape.h"
#include <iomanip>
#include <sstream>

class CLineSegment : public CShape
{
public:
	CLineSegment(CPoint startPoint, CPoint endPoint, uint32_t outlineColor);

	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

    void Draw(ICanvas& canvas) const override;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};