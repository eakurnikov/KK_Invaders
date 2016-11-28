#include "Gun.hpp"
#include "logger.hpp"

Gun::Gun()
{
  m_isAlive = true;
  m_ammo = 100;
  m_firingRate = GUN_FIRING_RATE;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = Point2D(SPACE_WIDTH / 2.0f, 0.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation);
}

Gun::Gun(Point2D const & obj)
{
  m_isAlive = true;
  m_ammo = 100;
  m_firingRate = GUN_FIRING_RATE;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation);
}

Gun::Gun(Point2D const & obj, unsigned int const Ammo, float firingRate)
{
  m_isAlive = true;
  m_ammo = Ammo;
  m_firingRate = firingRate;
  m_height = GUN_HEIGHT;
  m_width = GUN_WIDTH;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);

  Logger::Instance().Log(*this, ActionType::Creation);
}

void Gun::Move(float const shift)
{
  try
  {
    if (m_coordinate.x() + shift > SPACE_WIDTH || m_coordinate.x() + shift  < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate.x() += shift;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

void Gun::Shot()
{
  if (m_ammo != 0) m_ammo--;
  Bullet b = Bullet(*this);

  Logger::Instance().Log(*this, ActionType::Shot);
}

void Gun::SufferDamage(int amount)
{
  m_hp -= amount;
  Logger::Instance().Log(*this, ActionType::SufferDamage, amount);
}

void Gun::CauseDamage(int amount) const
{
  Logger::Instance().Log(*this, ActionType::CauseDamage, amount);
}

bool Gun::IsAlive() const
{
  return m_isAlive;
}

void Gun::PrintInfo(std::ostream & os)
{
  os << "--------------" << std::endl
     << "Gun" << std::endl << ((this->IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Center: " << this->GetCoordinate() << std::endl
     << " - Width: " << this->GetWidth() << std::endl
     << " - Height: " << this->GetHeight() << std::endl
     << " - Ammo: " << this->GetAmmo() << std::endl
     << " - Firing rate: " << this->GetFiringRate() << std::endl
     << "--------------" << std::endl;
}

std::ostream & operator << (std::ostream & os, Gun const & obj)
{
  os << "Gun (" << obj.GetCoordinate() << ") ";

  return os;
}
