#include "bullet.hpp"

Bullet::Bullet(Ray2D const & direction, Point2D const & startPosition)
  : m_direction(direction)
{
  m_speed = BULLET_SPEED;
  m_body = Box2D(startPosition, BULLET_HEIGHT, BULLET_WIDTH);
  m_hp = BULLET_HIT_POINTS;
}

Ray2D const & Bullet::GetDirection() const
{
  return m_direction;
}

void Bullet::Move(float const xShift, float const yShift)
{

}

unsigned int const Bullet::GetDamage() const
{
  return m_damage;
}
