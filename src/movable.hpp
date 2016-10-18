#pragma once

#include "gameentity.hpp"

class Movable : public GameEntity
{
public:
  virtual ~Movable() = default;
  virtual void Move(float const xShift, float const yShift) = 0;
  float const GetSpeed() const;

protected:
  float m_speed = 0;
};
