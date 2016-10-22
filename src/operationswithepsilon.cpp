#include "operationswithepsilon.h"

bool OperationsWithEpsilon::EqualWithEps(float const a, float const b)
{
  return fabs(a - b) < kEps;
}

bool OperationsWithEpsilon::EqualWithEps(float const a)
{
  return fabs(a) < kEps;
}

