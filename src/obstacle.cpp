#include "obstacle.hpp"

Obstacle::Obstacle()
{
  m_isAlive = true;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = {m_width / 2.0f, m_height / 2.0f};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Obstacle::Obstacle(Point2D const & obj)
{
  m_isAlive = true;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Obstacle::Obstacle(Box2D const & obj)
{
  m_isAlive = true;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

bool Obstacle::IsAlive() const
{
  return m_isAlive;
}

std::ostream & operator << (std::ostream & os, Obstacle const & obj)
{
  os << "Obstacle" << std::endl << ((obj.IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Health: " << obj.GetHP() << std::endl
     << " - Center: " << obj.GetCoordinate() << std::endl
     << " - Width: " << obj.GetWidth() << std::endl
     << " - Height: " << obj.GetHeight() << std::endl;

  return os;
}
