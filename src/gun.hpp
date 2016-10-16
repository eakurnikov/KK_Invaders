#pragma once

#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Gun : public Movable
{
public:
  Gun() = default;

  Gun(unsigned int const Ammo);

  void Move(float const shift);

  void Shot();

private:
  unsigned int m_ammo = 0;
  Point2D m_coordinate = {0.0f, 0.0f};
};
