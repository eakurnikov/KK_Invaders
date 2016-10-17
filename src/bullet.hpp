#pragma once

#include "defaultvalues.hpp"
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
  Bullet();

  Bullet(float speed, float damage);

  Bullet(Point2D const & obj);

  Bullet(Point2D const & obj, float speed, float damage);

  Bullet(Ray2D const & obj);

  Bullet(Ray2D const & obj, float speed, float damage);

  void Move() override;

  float GetDamage();

  Ray2D GetDirection();

private:
  float m_damage = 0;
  Ray2D m_trajectory = {0.0f, 0.0f, 0.0f, 0.0f};
};

