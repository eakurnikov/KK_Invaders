#include "Gun.h"

//Gun::Gun(unsigned int const Ammo) : m_ammo(Ammo) {}

void Gun::Move(float const shift)
{
  m_coordinate.x() += shift;
}

void Gun::Shot()
{
  m_ammo--;
}

