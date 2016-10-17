#pragma once

#include "box2d.hpp"
#include "defaultvalues.hpp"

class GameEntity
{
public:
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
