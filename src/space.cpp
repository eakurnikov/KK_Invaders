#include "space.hpp"

Space::Space()
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = {0.5f, 0.5f};
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Space::Space(Point2D const & obj)
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Space::Space(Box2D const & obj)
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

