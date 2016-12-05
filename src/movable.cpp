#include <cmath>
#include "movable.hpp"

void Movable::SetSpeed(float speed)
{
  m_speed = speed;
}

float Movable::GetSpeed() const
{
  return m_speed;
}

Movable const & Movable::Move()
{
  m_coordinate += m_speed;
}
