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

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
}

Alien::Alien(Point2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
}

Alien::Alien(Box2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;

  Logger::Instance().Log(*this, ActionType::Creation, std::cout);
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
  Bullet b = Bullet(*this);
  Logger::Instance().Log(*this, ActionType::Shot, std::cout);
}

void Alien::SufferDamage(int amount)
{
  m_hp -= amount;
  Logger::Instance().Log(*this, ActionType::SufferDamage, amount, std::cout);
}

void Alien::CauseDamage(int amount) const
{
  Logger::Instance().Log(*this, ActionType::CauseDamage, amount, cout);
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

void Alien::PrintInfo(std::ostream & os)
{
  os << "--------------" << std::endl
     << "Alien" << std::endl << ((this->IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Center: " << this->GetCoordinate() << std::endl
     << " - Width: " << this->GetWidth() << std::endl
     << " - Height: " << this->GetHeight() << std::endl
     << " - X Shift: " << this->GetXshift() << std::endl
     << " - Y Shift: " << this->GetYshift() << std::endl
     << " - Firing rate: " << this->GetFiringRate() << std::endl
     << "--------------" << std::endl;
}

std::ostream & operator << (std::ostream & os, Alien const & obj)
{
  os << "Alien (" << obj.GetCoordinate() << ") ";

  return os;
}
