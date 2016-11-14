#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "movable.hpp"
#include "alien.hpp"
#include "gun.hpp"
#include "obstacle.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include "logger.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include <vector>

class Bullet : public Movable
{
public:
  Bullet();

  Bullet(Shootable & shooter);

  Bullet(Ray2D const & obj, Shootable & shooter);

  Bullet(Ray2D const & obj, float speed, float damage, Shootable & shooter);

  void Move() override;

  bool IsAlive() const;

  void SetDamage(float damage);

  float GetDamage() const;

  Ray2D GetTrajectory() const;

  Shootable * GetShooter() const;

  void Notify() const;

  void Hit(GameEntity & obj);

  void PrintInfo(std::ostream & os) override;

private:

  bool m_isAlive = false;

  float m_damage = BULLET_DAMAGE;

  Ray2D m_trajectory = {0.0f, 1.0f, 0.0f, 0.0f};

  Shootable * m_viewerFirst;

  GameEntity * m_viewerSecond;
};

std::ostream & operator<<(std::ostream & os, Bullet const & obj);
