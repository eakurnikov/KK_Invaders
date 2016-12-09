#include <cmath>
#include "gameentity.hpp"
#include "logger.hpp"

GameEntity::GameEntity()
{
  m_isCreated = true;
  m_isAlive = true;
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
    m_body = Box2D(coordinate, m_width, m_height);
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

Point2D const & GameEntity::GetCoordinate() const
{
  return m_coordinate;
}

Box2D const & GameEntity::GetBody() const
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

bool GameEntity::DoObjectsIntersect(GameEntity const & obj1, GameEntity const & obj2)
{
  Box2D b1 = obj1.GetBody();
  Box2D b2 = obj2.GetBody();
  if (b1.rightBottomPoint().x() < b2.leftTopPoint().x()) return false; // a is left of b
  if (b1.leftTopPoint().x() > b2.rightBottomPoint().x()) return false; // a is right of b
  if (b1.rightBottomPoint().y() < b2.leftTopPoint().y()) return false; // a is above b
  if (b1.leftTopPoint().y() > b2.rightBottomPoint().y()) return false; // a is below b
  return true; // boxes overlap
}

void GameEntity::Kill()
{
  m_isAlive = false;
  m_coordinate = Point2D(-100.0f, -100.0f);
}
