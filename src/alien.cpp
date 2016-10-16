#include "alien.hpp"

//Alien::Alien(unsigned int const Ammo) : m_ammo(Ammo) {}

void Alien::Move()
{
  m_coordinate.x() += m_xShift;
}

void Alien::MoveDown()
{
  m_coordinate.y() -= m_yShift;
}

void Alien::Shot()
{

}

