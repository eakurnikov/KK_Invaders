#include "alien.hpp"
#include "bullet.hpp"
#include "logger.hpp"

Alien::Alien()
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = Point2D(SPACE_WIDTH / 2.0f, SPACE_HEIGHT / 2.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);
}

Alien::Alien(Point2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

Alien::Alien(Box2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

void Alien::Move()
{
  try
  {
    if (m_coordinate.x() + m_xShift > SPACE_WIDTH || m_coordinate.x() + m_xShift  < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate.x() += m_xShift;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

void Alien::MoveDown()
{
  try
  {
    if (m_coordinate.y() - m_xShift < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate.y() -= m_yShift;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

void Alien::Shot()
{
  Bullet b;
  Logger::Log(*this, ActionType::Shot, std::cout);
}

bool Alien::IsAlive() const
{
  return m_isAlive;
}

float Alien::GetXshift() const
{
  return m_xShift;
}

float Alien::GetYshift() const
{
  return m_yShift;
}

std::ostream & operator << (std::ostream & os, Alien const & obj)
{
  os << "Alien" << std::endl << ((obj.IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Center: " << obj.GetCoordinate() << std::endl
     << " - Width: " << obj.GetWidth() << std::endl
     << " - Height: " << obj.GetHeight() << std::endl
     << " - X Shift: " << obj.GetXshift() << std::endl
     << " - Y Shift: " << obj.GetYshift() << std::endl
     << " - Firing rate: " << obj.GetFiringRate() << std::endl;

  return os;
}
