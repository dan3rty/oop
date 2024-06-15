#pragma once

#include "IPoliceMan.h"
#include "ICar.h"

class IPoliceCar : public ICar<IPoliceMan>
{
};