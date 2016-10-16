#include "Gun.hpp"

Gun::Gun()
{
  m_isAlive = true;
}

Gun::Gun(unsigned int const Ammo)
{
  m_isAlive = true;
  m_ammo = Ammo;
}

Gun::Gun(Point2D const & obj)
{
  m_isAlive = true;
  m_coordinate = obj;
  m_body = Box2D(obj, 10, 10);
}

Gun::Gun(Box2D const & obj)
{
  m_isAlive = true;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

Gun::Gun(Point2D const & obj, unsigned int const Ammo)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_coordinate = obj;
  m_body = Box2D(obj, 10, 10);
}

Gun::Gun(Box2D const & obj, unsigned int const Ammo)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

Gun::Gun(std::initializer_list<float> const & lst)
{
  m_isAlive = true;
  m_coordinate = Point2D(lst);
  m_body = Box2D(m_coordinate, 10, 10);
}

void Gun::Move(float const shift)
{
  m_coordinate.x() += shift;
}
