#include <cmath>
#include "movable.hpp"

float Movable::GetSpeed()
{
  return m_speed;
}

void Movable::Move()
{
  m_coordinate += m_speed;
}
