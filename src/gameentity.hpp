#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class GameEntity
{
public:
  GameEntity();

  virtual ~GameEntity() = default;

  virtual void Damage(int amount);

  bool IsCreated() const;

  unsigned int GetHP() const;

  Point2D GetCoordinate() const;

  Box2D GetBody() const;

  float GetWidth() const;

  float GetHeight() const;

protected:
  bool m_isCreated = false;
  unsigned int m_hp = 0;
  float m_height, m_width = 0.0f;
  Point2D m_coordinate = {0.0f, 0.0f};
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};

/*template <typename T>
std::ostream & operator << (std::ostream & os, T const & obj)
{
  os << typeid(obj).name() << " {" << obj.GetCoordinate() << "}";
  return os;
}*/

