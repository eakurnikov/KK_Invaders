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
  virtual ~Movable() = default;
  virtual void Move();

private:
  Point2D m_coordinate = {0.0f, 0.0f};
  Point2D m_speed = {0.0f, 0.0f};
};

