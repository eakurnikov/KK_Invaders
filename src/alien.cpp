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
  m_aim = false;

  Logger::Instance().Log(*this, ActionType::Creation);
}

Alien::Alien(Point2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
  m_aim = false;

  Logger::Instance().Log(*this, ActionType::Creation);
}

Alien::Alien(Box2D const & obj)
{
  m_isAlive = true;
  m_firingRate = ALIEN_FIRING_RATE;
  m_height = ALIEN_HEIGHT;
  m_width = ALIEN_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;
  m_aim = false;

  Logger::Instance().Log(*this, ActionType::Creation);
}

Alien const & Alien::Move()
{
  if(m_isAlive)
    m_coordinate.x() += m_xShift;
  return *this;
}

Alien & Alien::MoveDown()
{
  if(m_isAlive)
    m_coordinate.y() -= m_yShift;
  return *this;
}

void Alien::Shot()
{
  Bullet b = Bullet(*this);
  Logger::Instance().Log(*this, ActionType::Shot);
}

void Alien::SufferDamage(int amount)
{
  m_hp -= amount;
  if (m_hp > 0)
    Logger::Instance().Log(*this, ActionType::SufferDamage, amount);
  else
    {
      Logger::Instance().Log(*this, ActionType::Destroying);
      Kill();
    }
}

void Alien::CauseDamage(int amount) const
{
  Logger::Instance().Log(*this, ActionType::CauseDamage, amount);
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

void Alien::Refract()
{
  m_xShift *= -1;
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
