#include "alien.hpp"
#include "bullet.hpp"

Alien::Alien()
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = Point2D(SPACE_WIDTH / 2.0f, SPACE_HEIGHT / 2.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Alien::Alien(Point2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Alien::Alien(Box2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
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

bool Alien::IsAlive() const
{
  return m_isAlive;
}

float Alien::GetXshift() const
{
  return m_xShift;
}

float Alien::GetYshift() const
{
  return m_yShift;
}
