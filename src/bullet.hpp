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
  Ray2D m_direction = {0.0f, 0.0f, 0.0f, 0.0f};
};

