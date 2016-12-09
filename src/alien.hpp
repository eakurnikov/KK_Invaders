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
#include <vector>

class Alien : public Shootable
{
public:

  Alien();

  Alien(Point2D const & obj);

  Alien(Box2D const & obj);

  Alien const & Move() override;

  Alien & MoveDown();

  void Shot() override;

  void SufferDamage(int amount) override;

  void CauseDamage(int amount) const override;

  bool IsAlive() const;

  float GetXshift() const;

  float GetYshift() const;

  void Refract();

  void PrintInfo(std::ostream & os) override;

private:

  float m_yShift = 5.0f;

  float m_xShift = 1.0f;

};

std::ostream & operator << (std::ostream & os, Alien const & obj);
