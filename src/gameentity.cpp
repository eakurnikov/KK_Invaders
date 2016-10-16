#include "gameentity.hpp"

Point2D GameEntity::GetCoordinate()
{
  return m_coordinate;
}

void GameEntity::Damage(int amount)
{
  m_hp -= amount;
}
