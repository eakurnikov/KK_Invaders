#include "obstacle.hpp"

Obstacle::Obstacle(Point2D const & position)
{
  m_body = Box2D(position, OBSTACLE_HEIGHT, OBSTACLE_WIDTH);
  m_hp = OBSTACLE_HIT_POINTS;
}
