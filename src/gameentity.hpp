#pragma once

#include "box2d.hpp"
#include "defaultvalues.hpp"

class GameEntity
{
public:
  //virtual ~GameEntity() = default;
  //virtual GameEntity(Point2D const & centerPosition);
  //GameEntity(Box2D const & box);

  bool IsAlive() const;
  void Destroy();  

  unsigned int const GetHP() const;
  Point2D const GetCoordinate() const;
  Box2D const & GetBody() const;
  float const GetWidth() const;
  float const GetHeight() const;

protected:
  Box2D m_body;
  unsigned int m_hp;
};
