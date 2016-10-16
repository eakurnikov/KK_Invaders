#include "alien.hpp"

//Alien::Alien(unsigned int const Ammo) : m_ammo(Ammo) {}

void Alien::Move(float shift)
{
  m_coordinate.x() += shift;
}

