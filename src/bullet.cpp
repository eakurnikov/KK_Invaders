#include "bullet.hpp"

Bullet::Bullet()
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = Point2D(m_width / 2.0f, m_height / 2.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = Ray2D(Point2D(m_coordinate.x(), m_coordinate.y() + m_speed), m_coordinate);
}

Bullet::Bullet(Ray2D const & obj)
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;
}

Bullet::Bullet(Ray2D const & obj, float speed, float damage)
{
  m_isAlive = true;
  m_damage = damage;
  m_speed = speed;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;
}

void Bullet::Move()
{
  m_coordinate.y() += m_speed;
}

bool Bullet::IsAlive() const
{
  return m_isAlive;
}

void Bullet::SetDamage(float damage)
{
  m_damage = damage;
}

float Bullet::GetDamage() const
{
  return m_damage;
}

Ray2D Bullet::GetTrajectory() const
{
  return m_trajectory;
}

