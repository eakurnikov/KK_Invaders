#include "bullet.hpp"
#include "logger.hpp"

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
}

Bullet::Bullet(Ray2D const & obj)
{
  m_isAlive = true;
  m_damage = BULLET_DAMAGE;
  m_speed = BULLET_SPEED;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;
}

Bullet::Bullet(Ray2D const & obj, float speed, float damage)
{
  m_isAlive = true;
  m_damage = damage;
  m_speed = speed;
  m_height = BULLET_HEIGHT;
  m_width = BULLET_WIDTH;
  m_coordinate = obj.initial();
  m_body = Box2D(m_coordinate, m_width, m_height);
  m_trajectory = obj;
}

void Bullet::Move()
{
  try
  {
    if (m_coordinate.y() + m_speed > SPACE_HEIGHT || m_coordinate.y() + m_speed  < 0) throw std::invalid_argument("Coodinate is out of Space!");
    m_coordinate.y() += m_speed;
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

//TODO: добавить вывод в лог, кто нанес урон пуле
void Bullet::Hit(Alien & obj)
{
  obj.Damage(m_damage);
  Logger::Log(obj, ActionType::SufferDamage, cout);
}

//TODO: добавить вывод в лог, кто нанес урон пушке
void Bullet::Hit(Gun & obj)
{
  obj.Damage(m_damage);
  Logger::Log(obj, ActionType::SufferDamage, cout);
}

//TODO: добавить вывод в лог, кто нанес урон препятствию
void Bullet::Hit(Obstacle & obj)
{
  obj.Damage(m_damage);
  Logger::Log(obj, ActionType::SufferDamage, cout);
}

std::ostream & operator << (std::ostream & os, Bullet const & obj)
{
  os << "Bullet" << std::endl << ((obj.IsAlive() == true) ? " - Alive" : " - Dead") << std::endl
     << " - Trajectory: " << obj.GetTrajectory() << std::endl
     << " - Speed: " << obj.GetSpeed() << std::endl
     << " - Damage: " << obj.GetDamage() << std::endl
     << " - Width: " << obj.GetWidth() << std::endl
     << " - Height: " << obj.GetHeight() << std::endl;

  return os;
}
