#pragma once

#include "shootable.hpp"

class Alien : public Shootable
{
public:
  Alien(Point2D const & position);
  void Move(float const xShift, float const yShift) override;
  void Move();
  void Shot() override;

  float const GetXshift() const;
  float const GetYshift() const;

private:
  float m_xShift = ALIEN_XSHIFT;
  float m_yShift = ALIEN_YSHIFT;
};
