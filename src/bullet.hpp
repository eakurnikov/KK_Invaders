#pragma once

#include "movable.hpp"
#include "ray2d.hpp"

class Bullet : public Movable
{
public:
  Bullet(Ray2D const & direction, Point2D const & startPosition);
  void Move(float const xShift, float const yShift) override;
  Ray2D const & GetDirection() const;
  unsigned int const GetDamage() const;

private:
  unsigned int m_damage = BULLET_DAMAGE;
  Ray2D m_direction;
};
