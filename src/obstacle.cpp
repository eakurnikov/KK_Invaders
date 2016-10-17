#include "obstacle.hpp"

Obstacle::Obstacle()
{
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = {m_width / 2, m_height / 2};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Obstacle::Obstacle(Point2D const & obj)
{
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Obstacle::Obstacle(Box2D const & obj)
{
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}


