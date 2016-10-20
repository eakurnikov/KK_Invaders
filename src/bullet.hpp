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

  Bullet(Ray2D const & obj);

  Bullet(Ray2D const & obj, float speed, float damage);

  void Move() override;

  bool IsAlive();

  float GetDamage();

  Ray2D GetTrajectory();

private:
  bool m_isAlive = false;
  float m_damage = BULLET_DAMAGE;
  Ray2D m_trajectory = {0.0f, 1.0f, 0.0f, 0.0f};
};

