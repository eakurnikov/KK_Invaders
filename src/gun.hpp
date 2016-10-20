#pragma once

#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "movable.hpp"
#include "shootable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Gun : public Shootable
{
public:
  Gun();

  Gun(Point2D const & obj);

  Gun(Point2D const & obj, unsigned int const Ammo, float rapidity);

  void Move(float const shift);

  bool IsAlive();

private:
  bool m_isAlive = false;
};
