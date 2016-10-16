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

class Alien : public Shootable
{
public:
  Alien() = default;

  void Move() override;

  void MoveDown();

  void Shot() override;

private:
  bool m_isAlive = false;
  float const m_yShift = 0;
  float const m_xShift = 0;
};

