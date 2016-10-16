#include "gameentity.hpp"

GameEntity::GameEntity()
{
  m_isCreated = true;
  m_hp = 100;
  m_height = 1;
  m_width = 1;
  m_coordinate = {0.5f, 0.5f};
  m_body = {0.0f, 0.0f, 1.0f, 1.0f};
}

GameEntity::GameEntity(Point2D const & obj)
{
  m_isCreated = true;
  m_hp = 100;
  m_height = 1;
  m_width = 1;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

GameEntity::GameEntity(Point2D const & obj, float width, float height)
{
  m_isCreated = true;
  m_hp = 100;
  m_height = height;
  m_width = width;
  m_coordinate = obj;
  m_body = Box2D(obj, m_width, m_height);
}

GameEntity::GameEntity(Box2D const & obj)
{
  m_isCreated = true;
  m_hp = 100;
  m_height = 1;
  m_width = 1;
  m_coordinate = obj.GetCenter();
  m_body = obj;
}

GameEntity::GameEntity(std::initializer_list<float> const & lst)
{
  m_isCreated = true;
  m_hp = 100;
  m_height = 1;
  m_width = 1;
  m_body = lst;
  m_coordinate = m_body.GetCenter();
}

Point2D GameEntity::GetCoordinate()
{
  return m_coordinate;
}

void GameEntity::Damage(int amount)
{
  m_hp -= amount;
}
