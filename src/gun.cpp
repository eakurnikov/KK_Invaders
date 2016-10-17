#include "Gun.hpp"

Gun::Gun()
{
  m_body = Box2D(Point2D(SPACE_WIDTH / 2 - GUN_WIDTH / 2, 0.0f), GUN_HEIGHT, GUN_WIDTH);
  m_speed = GUN_SPEED;
  m_rapidity = GUN_RAPIDITY;
  m_hp = GUN_HIT_POINTS;
}

Gun::Gun(Point2D const & centerPosition)
{
  m_body = Box2D(centerPosition, GUN_HEIGHT, GUN_WIDTH);
  m_speed = GUN_SPEED;
  m_rapidity = GUN_RAPIDITY;
  m_hp = GUN_HIT_POINTS;
}

void Gun::Move(float const xShift, float const yShift) {}

void Gun::Shot() {}

unsigned int const Gun::GetNumberOfLives () const { return m_numberOfLives; }

void Gun::DecreaseOneLife() { m_numberOfLives--; }

bool Gun::IsGameOver() const { return (m_numberOfLives > 0) ? false : true; }
