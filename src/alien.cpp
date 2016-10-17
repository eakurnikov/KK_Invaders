#include "alien.hpp"

Alien::Alien(Point2D const & position)
{
  m_body = Box2D(position, ALIEN_HEIGHT, ALIEN_WIDTH);
  m_speed = START_ALIEN_SPEED;
  m_rapidity = ALIEN_RAPIDITY;
  m_hp = ALIEN_HIT_POINTS;
}

void Alien::Move()
{

}

void Alien::Move(float const xShift, float const yShift)
{

}

void Alien::Shot()
{

}

float const Alien::GetXshift() const
{
  return m_xShift;
}
float const Alien::GetYshift() const
{
  return m_yShift;
}
