#pragma once

#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Shootable : public Movable
{
public:
  Shootable();

  virtual ~Shootable() = default;

  virtual void Shot();

protected:
  unsigned int m_ammo = 0;
  float m_rapidity = 0;
};

