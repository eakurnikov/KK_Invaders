#pragma once

#include <cstdlib>
#include <cmath>

class Star
{
public:
  Star() = default;
  float const & getT() const;
  float const & getX() const;
  float const & getY() const;

private:
  float m_T = std::rand() % 1000;
  float m_x = (float)std::rand() / RAND_MAX;
  float m_y = (float)std::rand() / RAND_MAX;
};
