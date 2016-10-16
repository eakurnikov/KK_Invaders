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
  unsigned int m_hp = 100;
  float m_rapidity = 0;
  float const m_yShift = 0;
  float const m_xShift = 0;
  float const m_height, m_width = 0;
  Point2D m_coordinate = {0.0f, 0.0f};
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};

