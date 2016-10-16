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
  Space() = default;

private:
  Box2D m_body = {0.0f, 0.0f, 0.0f, 0.0f};
};

