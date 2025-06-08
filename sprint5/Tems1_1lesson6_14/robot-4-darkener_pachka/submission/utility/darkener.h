#pragma once

#include "geometry.h"

class Darkener{
public:
    virtual ~Darkener() = default;
    virtual double GetDarkness(CoordinateF pos) const = 0;
};