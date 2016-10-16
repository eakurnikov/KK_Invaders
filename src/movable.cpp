#include "movable.hpp"

Movable::Movable()
{
  m_speed = {1.0f, 1.0f};
}

Movable::Movable(Point2D const & obj)
{
  m_speed = obj;
}

Movable::Movable(std::initializer_list<float> const & lst)
{
  m_speed = Point2D(lst);
}

