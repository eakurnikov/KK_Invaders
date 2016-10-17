#pragma once

#include "defaultvalues.hpp"
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

  float GetSpeed();

protected:
  float m_speed = 0;
};

