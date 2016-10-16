#pragma once

#include "gameentity.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Movable : public GameEntity
{
public:
  Movable();

  Movable(Point2D const & obj);

  Movable(std::initializer_list<float> const & lst);

  virtual ~Movable() = default;

  virtual void Move() = 0;

protected:
  Point2D m_speed = {0.0f, 0.0f};
};

