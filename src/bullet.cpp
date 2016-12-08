#include "bullet.hpp"

Bullet::Bullet()
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = Point2D(m_width / 2.0f, m_height / 2.0f);
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = Ray2D(Point2D(m_coordinate.x(), m_coordinate.y() + m_speed), m_coordinate);

  m_viewerFirst = nullptr;
}

Bullet::~Bullet()
{
  m_isAlive = false;
  m_coordinate = {0.0f, 0.0f};
  m_body = Box2D(m_coordinate, 0.0f, 0.0f);
}

Bullet::Bullet(Shootable & shooter)
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  shooter.GetAim() == true ? m_speed = BULLET_SPEED : m_speed = -1 * BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = shooter.GetCoordinate();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = Ray2D(Point2D(m_coordinate.x(), m_coordinate.y() + m_speed), m_coordinate);

  m_viewerFirst = &shooter;
}

Bullet::Bullet(Ray2D const & obj, Shootable & shooter)
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  shooter.GetAim() == true ? m_speed = BULLET_SPEED : m_speed = -1 * BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;

  m_viewerFirst = &shooter;
}

Bullet::Bullet(Ray2D const & obj, float speed, float damage, Shootable & shooter)
{
  m_isAlive = true;
  m_damage = damage;
  shooter.GetAim() == true ? m_speed = speed : m_speed = -1 * speed;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;

  m_viewerFirst = &shooter;
}

Bullet const & Bullet::Move()
{
  try
  {
    //if (m_coordinate.y() + m_speed > SPACE_HEIGHT || m_coordinate.y() + m_speed  < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate.y() += m_speed;
    return *this;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

bool Bullet::IsAlive() const
{
  return m_isAlive;
}

void Bullet::SetDamage(float damage)
{
  try
  {
    if (damage <= 0) throw std::invalid_argument("Damage <= 0.");
    m_damage = damage;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

float Bullet::GetDamage() const
{
  return m_damage;
}

Ray2D Bullet::GetTrajectory() const
{
  return m_trajectory;
}

Shootable * Bullet::GetShooter() const
{
  return m_viewerFirst;
}

void Bullet::Notify() const
{
  m_viewerFirst->CauseDamage(m_damage);
  m_viewerSecond->SufferDamage(m_damage);
}

void Bullet::Hit(GameEntity & obj)
{
  m_viewerSecond = &obj;
  Notify();
}

void Bullet::PrintInfo(std::ostream & os)
{
  os << "--------------" << std::endl
     << "Bullet" << std::endl << ((this->IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Trajectory: " << this->GetTrajectory() << std::endl
     << " - Speed: " << this->GetSpeed() << std::endl
     << " - Damage: " << this->GetDamage() << std::endl
     << " - Width: " << this->GetWidth() << std::endl
     << " - Height: " << this->GetHeight() << std::endl
     << "--------------" << std::endl;
}

std::ostream & operator << (std::ostream & os, Bullet const & obj)
{
  os << "Bullet (" << obj.GetCoordinate() << ") ";

  return os;
}
