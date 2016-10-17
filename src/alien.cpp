#include "alien.hpp"
#include "bullet.hpp"

Alien::Alien()
{
  m_isAlive = true;
  m_rapidity = ALIEN_RAPIDITY;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = {0.5f, 0.5f};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Alien::Alien(Point2D const & obj, float rapidity)
{
  m_isAlive = true;
  m_rapidity = rapidity;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Alien::Alien(Box2D const & obj, float rapidity)
{
  m_isAlive = true;
  m_rapidity = rapidity;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

void Alien::Move()
{
  m_coordinate.x() += m_xShift;
}

void Alien::MoveDown()
{
  m_coordinate.y() -= m_yShift;
}

void Alien::Shot()
{
  Bullet();
}

bool Alien::IsAlive()
{
  return m_isAlive;
}

float Alien::GetXshift()
{
  return m_xShift;
}

float Alien::GetYshift()
{
  return m_yShift;
}
