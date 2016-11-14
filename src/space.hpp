#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "obstacle.hpp"
#include "gun.hpp"
#include "bullet.hpp"
#include "alien.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include "logger.hpp"
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

  void PrintInfo(std::ostream & os) override;

private:

  std::deque<Gun> m_gun;

  std::vector<Obstacle> m_obstacles;

  //std::list<Bullet> m_bullets;
  //Если убрать комментарий, по необъяснимым причинам компилятор ругается, что я не определил здесь буллет, хотя я включил сюда bullet.hpp

  std::list<Alien> m_aliens;
};

std::ostream & operator << (std::ostream & os, Space const & obj);
