#include "bullet.hpp"

Bullet::Bullet()
{
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = {0.5f, 0.5f};
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = {m_coordinate, m_coordinate + m_speed};
}

Bullet::Bullet(float speed, float damage)
{
  m_damage = damage;
  m_speed = speed;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = {0.5f, 0.5f};
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = {m_coordinate, m_coordinate + m_speed};
}

Bullet::Bullet(Point2D const & obj)
{
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = {m_coordinate, m_coordinate + m_speed};
}

Bullet::Bullet(Point2D const & obj, float speed, float damage)
{
  m_damage = damage;
  m_speed = speed;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = {obj, obj + m_speed};
}

Bullet::Bullet(Ray2D const & obj)
{
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

float Bullet::GetDamage()
{
  return m_damage;
}

Ray2D Bullet::GetDirection()
{
  return m_trajectory;
}

