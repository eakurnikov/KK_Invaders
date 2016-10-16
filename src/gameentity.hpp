#pragma once

#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class GameEntity
{
public:
  virtual ~GameEntity() = 0;
  virtual toString() = 0;

  virtual Point2D GetCoordinate();

  virtual void Damage(int amount);

protected:
  bool m_isCreated = false;
  unsigned int m_hp = 100;
  float const m_height, m_width = 0;
  Point2D m_coordinate = {0.0f, 0.0f};
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};

/*template <typename T>
std::ostream & operator << (std::ostream & os, T const & obj)
{
  os << typeid(obj).name() << " {" << obj.GetCoordinate() << "}";
  return os;
}*/

