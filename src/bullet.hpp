#pragma once

#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Bullet : public Movable
{
public:
  Bullet() = default;

  void Move() override;

private:
  float const m_damage = 0;
  float const m_height, m_width = 0;
  Point2D m_coordinate = {0.0f, 0.0f};
  Point2D m_speed = {0.0f, 0.0f};
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
  Ray2D m_direction = {0.0f, 0.0f, 0.0f, 0.0f};
};

