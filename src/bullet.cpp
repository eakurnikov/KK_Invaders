#include "bullet.hpp"

Bullet::Bullet()
{
  m_damage = 10;
  m_direction = {m_coordinate, m_coordinate + m_speed};
}

Bullet::Bullet(Point2D const & speed, float damage)
{
  m_damage = damage;
  m_speed = speed;
  m_direction = {m_coordinate, m_coordinate + m_speed};
}

Bullet::Bullet(Point2D const & position)
{
  m_damage = 10;
  m_direction = {position, position + m_speed};
}

Bullet::Bullet(Point2D const & position, Point2D const & speed, float damage)
{
  m_damage = damage;
  m_speed = speed;
  m_direction = {position, position + m_speed};
}

Bullet::Bullet(Ray2D const & obj)
{
  m_damage = 10;
  m_direction = obj;
}

Bullet::Bullet(Ray2D const & obj, Point2D const & speed, float damage)
{
  m_damage = damage;
  m_speed = speed;
  m_direction = obj;
}

Bullet::Bullet(std::initializer_list<float> const & lst)
{
  m_damage = 10;
  m_direction = {Point2D(lst), Point2D(lst) + m_speed};
}

void Bullet::Move()
{
  m_coordinate.y() += m_speed.y();
}

