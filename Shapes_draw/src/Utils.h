#pragma once

#include <iomanip>
#include <iostream>
#include <cstdint>
#include "CPoint.h"

void PrintColor(std::ostream& output, uint32_t color);
double GetDistance(const CPoint& p1, const CPoint& p2);