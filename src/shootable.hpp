#pragma once

#include "movable.hpp"

class Shootable : public Movable
{
public:
  virtual ~Shootable() = default;
  virtual void Shot() = 0;
  unsigned int const GetRapidity() const;

protected:
  unsigned int m_rapidity = 0;
};
