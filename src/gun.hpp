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
  Gun() = default;

  Gun(unsigned int const Ammo);

  void Move(float const shift);

private:
  bool m_isAlive = false;
};
