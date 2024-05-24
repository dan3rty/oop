#pragma once

#include "ICanvas.h"
#include <string>
#include <cstdint>

//добавить CanvasDrawable
class IShape
{
public:
    [[nodiscard]] virtual double GetArea() const = 0;
	[[nodiscard]] virtual double GetPerimeter() const = 0;
	[[nodiscard]] virtual std::string ToString() const = 0;
	[[nodiscard]] virtual uint32_t GetOutlineColor() const = 0;

    virtual void Draw(ICanvas& canvas) const = 0;

    //выяснить и доложить
	virtual ~IShape() = default;
};