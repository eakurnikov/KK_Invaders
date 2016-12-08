#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "point2d.hpp"
#include "gameentity.hpp"
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

  virtual ~GameEntity() = default;

  virtual void SufferDamage(int amount);

  bool IsCreated() const;

  void SetHP(unsigned int hp);

  unsigned int GetHP() const;

  void SetCoordinate(Point2D const & coordinate);

  Point2D const & GetCoordinate() const;

  void SetX(float const & x);

  void SetY(float const & y);

  Box2D const & GetBody() const;

  float GetWidth() const;

  float GetHeight() const;

  virtual void PrintInfo(std::ostream & os);

  static bool DoObjectsIntersect(GameEntity const & obj1, GameEntity const & obj2);

  void Kill();

protected:

  GameEntity();

  bool m_isAlive = false;

  bool m_isCreated = false;

  unsigned int m_hp = 0;

  float m_height, m_width = 0.0f;

  Point2D m_coordinate = {0.0f, 0.0f};

  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};

  std::string m_info = "";
};

template <typename T, template <typename, typename> class C>
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

