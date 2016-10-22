#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "movable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Shootable : public Movable
{
public:
  virtual ~Shootable() = default;

  virtual void Shot();

  unsigned int GetAmmo() const;

  void SetFiringRate(float firingRate);

  float GetFiringRate() const;

protected:
  unsigned int m_ammo = 0;
  float m_firingRate = 0.0f;
};

