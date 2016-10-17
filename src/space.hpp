#pragma once

#include "gameentity.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include <vector>

class Space
{
public:
  Space() = default;
  Space(float const height, float const width);
  Box2D const & GetField() const;
  float const GetWidth() const;
  float const GetHeight() const;

private:
  Box2D m_field = Box2D(0.0f, 0.0f, SPACE_WIDTH, SPACE_HEIGHT);
  Gun m_gun;
  std::vector<Obstacle> m_obstacles;
  std::vector<Bullet> m_bullets;
  std::vector<Alien> m_aliens;
};
