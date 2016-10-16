#pragma once

#include "gameentity.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Space : public GameEntity
{
public:
  Space();

  Space(Point2D const & obj);

  Space(Box2D const & obj);

  Space(std::initializer_list<float> const & lst);

private:
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};

