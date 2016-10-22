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

bool GameEntity::IsCreated() const
{
  return m_isCreated;
}

unsigned int GameEntity::GetHP() const
{
  return m_hp;
}

Point2D GameEntity::GetCoordinate() const
{
  return m_coordinate;
}

Box2D GameEntity::GetBody() const
{
  return m_body;
}

float GameEntity::GetWidth() const
{
  return m_width;
}

float GameEntity::GetHeight() const
{
  return m_height;
}
