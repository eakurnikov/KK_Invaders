#include "bullet.hpp"

void Bullet::Move()
{
  m_coordinate.y() += m_speed.y();
}

