#include "space.hpp"

Space::Space(float const height, float const width)
{
  m_field = Box2D(0.0f, 0.0f, height, width);
}

Box2D const & Space::GetField() const
{
  return m_field;
}

float const Space::GetWidth() const
{
  return m_field.Width();
}

float const Space::GetHeight() const
{
  return m_field.Height();
}
