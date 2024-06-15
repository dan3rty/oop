#pragma once

#include "IPerson.h"
#include "ICar.h"

class ITaxi : public ICar<IPerson>
{
};