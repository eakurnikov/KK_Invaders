#pragma once

#include "operationswithepsilon.h"
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

  void SetSpeed(float speed);

  float GetSpeed() const;

protected:

  Movable() = default;

  float m_speed = 0.0f;
};


