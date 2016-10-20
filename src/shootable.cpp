#include "shootable.hpp"
#include "bullet.hpp"
#include <iostream>

void Shootable::Shot()
{
  try
  {
    if (m_ammo == 0) throw std::invalid_argument("Ammo is empty.");
    m_ammo--;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
  }
  Bullet b = Bullet();
}

unsigned int Shootable::GetAmmo()
{
  return m_ammo;
}

float Shootable::GetRapidity()
{
  return m_rapidity;
}

