#include "shootable.hpp"
#include "bullet.hpp"
#include <iostream>

void Shootable::Shot()
{
  if (m_ammo != 0) m_ammo--;
  Bullet b = Bullet();
}

unsigned int Shootable::GetAmmo() const
{
  return m_ammo;
}

void Shootable::SetFiringRate(float firingRate)
{
  try
  {
    if (firingRate <= 0.0f) throw std::invalid_argument("Firing rate <= 0.");
    m_firingRate = firingRate;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

float Shootable::GetFiringRate() const
{
  return m_firingRate;
}

