#pragma once

#include "operationswithepsilon.h"
#include "defaultvalues.hpp"
#include "gameentity.hpp"
#include "movable.hpp"
#include "shootable.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>

class Gun : public Shootable
{
public:

  Gun();

  Gun(Point2D const & obj);

  Gun(Point2D const & obj, unsigned int const Ammo, float firingRate);

  void Move(float const shift);

  void Shot() override;

  void SufferDamage(int amount) override;

  void CauseDamage(int amount) const override;

  bool IsAlive() const;

  void PrintInfo(std::ostream & os) override;

private:

  bool m_isAlive = false;
};

std::ostream & operator << (std::ostream & os, Gun const & obj);
