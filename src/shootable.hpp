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

  virtual void Shot() = 0;

  unsigned int GetAmmo() const;

  void SetFiringRate(float firingRate);

  float GetFiringRate() const;

  virtual void CauseDamage(int amount) = 0;

  bool GetAim() const;

protected:

  Shootable() = default;

  unsigned int m_ammo = 0;

  float m_firingRate = 0.0f;

  bool m_aim = false;
};

