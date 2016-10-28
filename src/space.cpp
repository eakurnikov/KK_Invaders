#include "space.hpp"

Space::Space()
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = Point2D(m_width / 2.0f, m_height / 2.0f);
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

std::ostream & operator << (std::ostream & os, Space const & obj)
{
  os << "Space" << std::endl << ((obj.IsCreated() == true) ? " - Created" : " - Not created") << std::endl
     << " - Center: " << obj.GetCoordinate() << std::endl
     << " - Width: " << obj.GetWidth() << std::endl
     << " - Height: " << obj.GetHeight() << std::endl;

  return os;
}
