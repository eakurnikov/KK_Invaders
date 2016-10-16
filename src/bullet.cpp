#include "bullet.h"

void Bullet::Move()
{
  m_coordinate.y() += m_speed.y();
}

