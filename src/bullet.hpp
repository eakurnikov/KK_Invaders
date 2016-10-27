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

  bool IsAlive() const;

  void SetDamage(float damage);

  float GetDamage() const;

  Ray2D GetTrajectory() const;

  void Hit(Alien & obj);

  void Hit(Gun & obj);

  void Hit(Obstacle & obj);

private:
  bool m_isAlive = false;
  float m_damage = BULLET_DAMAGE;
  Ray2D m_trajectory = {0.0f, 1.0f, 0.0f, 0.0f};
  //TODO: добавить поле стрелка, добавить его инициализацию в конструкторы, добавить изменения в тесты, дописать Hit
  //GameEntity m_shooter = Gun();
};

std::ostream & operator<<(std::ostream & os, Bullet const & obj);
