#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Obstacle : public GameEntity
{
public:
  Obstacle();

  Obstacle(Point2D const & obj);

  Obstacle(Box2D const & obj);

  bool IsAlive() const;

private:
  bool m_isAlive = false;
};

std::ostream & operator << (std::ostream & os, Obstacle const & obj);
