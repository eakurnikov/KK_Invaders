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
#include <iostream>

class Alien : public Shootable
{
public:

  Alien();

  Alien(Point2D const & obj);

  Alien(Box2D const & obj);

  void Move() override;

  void MoveDown();

  void Shot() override;

  void SufferDamage(int amount) override;

  void CauseDamage(int amount) const override;

  bool IsAlive() const;

  float GetXshift() const;

  float GetYshift() const;

  void PrintInfo(std::ostream & os) override;

private:

  bool m_isAlive = false;

  float const m_yShift = 10.0f;

  float const m_xShift = 1.0f;

};

std::ostream & operator << (std::ostream & os, Alien const & obj);
