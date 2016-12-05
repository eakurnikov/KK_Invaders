#include <cmath>
#include "gameentity.hpp"
#include "logger.hpp"

GameEntity::GameEntity()
{
  m_isCreated = true;
  m_hp = 100;
}

void GameEntity::SufferDamage(int amount)
{

}

bool GameEntity::IsCreated() const
{
  return m_isCreated;
}

void GameEntity::SetHP(unsigned int hp)
{
  try
  {
    if (hp > 100) throw std::invalid_argument("HP must be <= 100!");
    m_hp = hp;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

unsigned int GameEntity::GetHP() const
{
  return m_hp;
}

void GameEntity::SetCoordinate(Point2D const & coordinate)
{
  try
  {
    //if (coordinate.x() > SPACE_WIDTH || coordinate.x() < 0 || coordinate.y() > SPACE_HEIGHT || coordinate.y() < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate = coordinate;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

void GameEntity::SetX(float const & x)
{
  m_coordinate.x() = x;
}

void GameEntity::SetY(float const & y)
{
  m_coordinate.y() = y;
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

void GameEntity::PrintInfo(std::ostream & os)
{

}
