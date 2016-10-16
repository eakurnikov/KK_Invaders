#include "alien.hpp"

Alien::Alien()
{
  m_isAlive = true;
}

Alien::Alien(Point2D const & obj)
{
  m_isAlive = true;
  m_coordinate = obj;
  m_body = Box2D(obj, 10, 10);
}

Alien::Alien(Box2D const & obj)
{
  m_isAlive = true;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

Alien::Alien(std::initializer_list<float> const & lst)
{
  m_isAlive = true;
  m_coordinate = Point2D(lst);
  m_body = Box2D(m_coordinate, 10, 10);
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

}

