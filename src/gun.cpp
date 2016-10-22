#include "Gun.hpp"

Gun::Gun()
{
  m_isAlive = true;
  m_ammo = 100;
  m_firingRate = GUN_FIRING_RATE;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = Point2D(SPACE_WIDTH / 2.0f, 0.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Gun::Gun(Point2D const & obj)
{
  m_isAlive = true;
  m_ammo = 100;
  m_firingRate = GUN_FIRING_RATE;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Gun::Gun(Point2D const & obj, unsigned int const Ammo, float firingRate)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_firingRate = firingRate;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

void Gun::Move(float const shift)
{
  m_coordinate.x() += shift;
}

bool Gun::IsAlive() const
{
  return m_isAlive;
}
