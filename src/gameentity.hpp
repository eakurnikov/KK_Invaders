#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include <vector>
#include <string>

class GameEntity
{
public:
  GameEntity();

  virtual ~GameEntity() = default;

  virtual void Damage(int amount);

  bool IsCreated() const;

  void SetHP(unsigned int hp);

  unsigned int GetHP() const;

  void SetCoordinate(Point2D const & coordinate);

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

template<typename T, template<typename, typename> class C>
std::ostream & operator << (std::ostream & os, C<T, std::allocator<T> > const & objs)
{
  for (auto const & obj : objs)
  os << obj << ' ';
  return os;
}

enum ActionType
{
  Creation, Destroying, Shot, CauseDamage, SufferDamage
};

