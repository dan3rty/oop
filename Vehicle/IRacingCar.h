#pragma once

#include "IRacer.h"
#include "ICar.h"

class IRacingCar : public ICar<IRacer>
{
};