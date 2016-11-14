#include "space.hpp"

Space::Space()
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = Point2D(m_width / 2.0f, m_height / 2.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
}

Space::Space(Point2D const & obj)
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
}

Space::Space(Box2D const & obj)
{
  m_height = SPACE_HEIGHT;
  m_width = SPACE_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
}

void Space::PrintInfo(std::ostream & os)
{
  os << "--------------" << std::endl
     << "Space" << std::endl << ((this->IsCreated() == true) ? " - Created" : " - Not created") << std::endl
     << " - Center: " << this->GetCoordinate() << std::endl
     << " - Width: " << this->GetWidth() << std::endl
     << " - Height: " << this->GetHeight() << std::endl
     << "--------------" << std::endl;
}

std::ostream & operator << (std::ostream & os, Space const & obj)
{
  os << "Space (" << obj.GetCoordinate() << ") ";

  return os;
}
