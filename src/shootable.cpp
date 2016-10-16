#include "shootable.hpp"

Shootable::Shootable()
{
  m_ammo = 100;
  m_rapidity = 1;
}

void Shootable::Shot()
{
  m_ammo--;
}

