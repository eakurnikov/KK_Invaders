#pragma once

#include "shootable.hpp"

class Gun : public Shootable
{
public:
  Gun();
  Gun(Point2D const & centerPosition);

  void Move(float const xShift, float const yShift) override;
  void Shot() override;

  unsigned int const GetNumberOfLives () const;
  void DecreaseOneLife();
  bool IsGameOver() const;

private:
 unsigned int m_numberOfLives = START_NUMBER_OF_LIFES;
};
