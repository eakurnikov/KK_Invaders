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

class Alien : public Shootable
{
public:
  Alien();

  Alien(Point2D const & obj, float rapidity);

  Alien(Box2D const & obj, float rapidity);

  void Move() override;

  void MoveDown();

  void Shot() override;

  bool IsAlive();

  float GetXshift();

  float GetYshift();

private:
  bool m_isAlive = false;
  float const m_yShift = 10;
  float const m_xShift = 1;
};

