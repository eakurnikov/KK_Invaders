#pragma once

#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Alien : public Movable
{
public:
  Alien() = default;

  void Move(float shift);

private:
  Point2D m_coordinate = {0.0f, 0.0f};
};

