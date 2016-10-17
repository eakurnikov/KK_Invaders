#include "Gun.hpp"

Gun::Gun()
{
  m_isAlive = true;
  m_ammo = 100;
  m_rapidity = GUN_RAPIDITY;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = {m_width / 2, m_height / 2};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Gun::Gun(unsigned int const Ammo)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_rapidity = GUN_RAPIDITY;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = {m_width / 2, m_height / 2};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Gun::Gun(Point2D const & obj)
{
  m_isAlive = true;
  m_ammo = 100;
  m_rapidity = GUN_RAPIDITY;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Gun::Gun(Box2D const & obj)
{
  m_isAlive = true;
  m_ammo = 100;
  m_rapidity = GUN_RAPIDITY;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

Gun::Gun(Point2D const & obj, unsigned int const Ammo, float rapidity)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_rapidity = rapidity;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Gun::Gun(Box2D const & obj, unsigned int const Ammo, float rapidity)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_rapidity = rapidity;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

void Gun::Move(float const shift)
{
  m_coordinate.x() += shift;
}

bool Gun::IsAlive()
{
  return m_isAlive;
}
