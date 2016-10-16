#pragma once

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

  Gun(unsigned int const Ammo);

  Gun(Point2D const & obj);

  Gun(Box2D const & obj);

  Gun(Point2D const & obj, unsigned int const Ammo);

  Gun(Box2D const & obj, unsigned int const Ammo);

  Gun(std::initializer_list<float> const & lst);

  void Move(float const shift);

private:
  bool m_isAlive = false;
};
