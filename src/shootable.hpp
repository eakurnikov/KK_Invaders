#pragma once

#include "movable.hpp"

class Shootable : public Movable
{
public:
  virtual ~Shootable() = default;
  virtual void Shot() = 0;
  unsigned int const GetVelocity() const;

protected:
  unsigned int m_velocity = 0;
};
