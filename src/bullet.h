#pragma once

#include <gameentity.h>
#include <movable.h>
#include <point2d.hpp>
#include <box2d.hpp>
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
  Point2D m_coordinate = {0.0f, 0.0f};
  Point2D m_speed = {0.0f, 0.0f};
};

