#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include <vector>
#include <list>
#include <deque>

class Space : public GameEntity
{
public:
  Space();

  Space(Point2D const & obj);

  Space(Box2D const & obj);

private:
  std::deque<Gun> m_gun;
  std::vector<Obstacle> m_obstacles;
  std::list<Bullet> m_bullets;
  std::list<Alien> m_aliens;
};

