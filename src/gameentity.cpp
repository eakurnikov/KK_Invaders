#include <cmath>
#include "gameentity.hpp"

GameEntity::GameEntity()
{
  m_isCreated = true;
  m_hp = 100;
}

void GameEntity::Damage(int amount)
{
  m_hp -= amount;
}

bool GameEntity::IsCreated()
{
  return m_isCreated;
}

unsigned int GameEntity::GetHP()
{
  return m_hp;
}

Point2D GameEntity::GetCoordinate()
{
  return m_coordinate;
}

Box2D GameEntity::GetBody()
{
  return m_body;
}

float GameEntity::GetWidth()
{
  return m_width;
}

float GameEntity::GetHeight()
{
  return m_height;
}
