#include "shootable.hpp"
#include "bullet.hpp"

void Shootable::Shot()
{
  m_ammo--;
  Bullet();
}

unsigned int Shootable::GetAmmo()
{
  return m_ammo;
}

float Shootable::GetRapidity()
{
  return m_rapidity;
}

