#include "obstacle.hpp"
#include "logger.hpp"

Obstacle::Obstacle()
{
  m_isAlive = true;
  m_hp = 500;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = {m_width / 2.0f, m_height / 2.0f};
  m_body = Box2D(m_coordinate, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation);
}

Obstacle::Obstacle(Point2D const & obj)
{
  m_isAlive = true;
  m_hp = 500;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation);
}

Obstacle::Obstacle(Box2D const & obj)
{
  m_isAlive = true;
  m_hp = 500;
  m_height = OBSTACLE_HEIGHT;
  m_width = OBSTACLE_WIDTH;
  m_coordinate = obj.GetCenter();
  m_body = obj;

  Logger::Instance().Log(*this, ActionType::Creation);
}

void Obstacle::SufferDamage(int amount)
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

bool Obstacle::IsAlive() const
{
  return m_isAlive;
}

void Obstacle::Resurrect()
{
  m_isAlive = true;
}

void Obstacle::PrintInfo(std::ostream & os)
{
  os << "--------------" << std::endl
     << "Obstacle" << std::endl << ((this->IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Health: " << this->GetHP() << std::endl
     << " - Center: " << this->GetCoordinate() << std::endl
     << " - Width: " << this->GetWidth() << std::endl
     << " - Height: " << this->GetHeight() << std::endl
     << "--------------" << std::endl;
}

std::ostream & operator << (std::ostream & os, Obstacle const & obj)
{
  os << "Obstacle (" << obj.GetCoordinate() << ") ";

  return os;
}
