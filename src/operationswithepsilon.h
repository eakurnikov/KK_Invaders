#pragma once

#include <cmath>
#include <functional>
#include <ostream>

class OperationsWithEpsilon
{
public:
  static float constexpr kEps = 1e-5;

  static bool EqualWithEps(float const a, float const b)
  {
    return fabs(a - b) < kEps;
  }

  static bool EqualWithEps(float const a)
  {
    return fabs(a) < kEps;
  }
};
