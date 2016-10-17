#include "gameentity.hpp"

bool GameEntity::IsAlive() const { return (m_hp > 0) ? true : false; }

void GameEntity::Destroy() {}

unsigned int const GameEntity::GetHP() const { return m_hp; }

Point2D const GameEntity::GetCoordinate() const { return m_body.GetCenter(); }

Box2D const & GameEntity::GetBody() const { return m_body; }

float const GameEntity::GetWidth() const { return m_body.Width(); }

float const GameEntity::GetHeight() const { return m_body.Height(); }
