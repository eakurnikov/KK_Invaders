#include "ray2d.hpp"

//float const kEps = 1e-5;

#define PI 3.14159265

// Конструкторы

// Конструктор с заданием двух координат, определяющих направление луча
Ray2D::Ray2D(float const direction_x, float const direction_y)
  : m_direction(direction_x, direction_y)
{
  Normalize();
}

// Конструктор с заданием четырех координат, определяющих направление луча и его начало
Ray2D::Ray2D(float const direction_x, float const direction_y, float const initial_x, float const initial_y)
  : m_direction(direction_x, direction_y)
  , m_initial(initial_x, initial_y)
{
  Normalize();
}

// Конструктор с заданием точки, определяющей направление луча
Ray2D::Ray2D(Point2D const & direction)
  : m_direction(direction)
{
  Normalize();
}

// Конструктор с заданием двух точек, определяющих направление луча и его начало
Ray2D::Ray2D(Point2D const & direction, Point2D const & initial)
  : m_direction(direction)
  , m_initial(initial)
{
  Normalize();
}

// Конструктор с заданием параметров на основе сущестующего луча
Ray2D::Ray2D(Ray2D const & obj)
  : m_direction(obj.m_direction)
  , m_initial(obj.m_initial)
{}

// Конструктор со списком иниациализации
Ray2D::Ray2D(std::initializer_list<Point2D> const & lst)
{
  Point2D * vals[] = { &m_direction, &m_initial };
  int const count = sizeof(vals) / sizeof(vals[0]);
  auto it = lst.begin();
  for (int i = 0; i < count && it != lst.end(); ++i, ++it)
  {
    *vals[i] = *it;
  }
  Normalize();
}

// Конструктор со списком иниациализации
Ray2D::Ray2D(std::initializer_list<float> const & lst)
{

  float * vals[] = { &m_direction.x(), &m_direction.y(), &m_initial.x(), &m_initial.y()};
  int const count = sizeof(vals) / sizeof(vals[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); ++i, ++it)
  {
    *vals[i] = *it;
  }
  Normalize();
}
// Операторы

// Оператор присваивания
Ray2D & Ray2D::operator = (Ray2D const & obj)
{
  if (this == &obj) return *this;
  m_initial = obj.m_initial;
  m_direction = obj.m_direction;
  return *this;
}

// Оператор логического равенства
bool Ray2D::operator == (Ray2D const & obj) const
{
  return m_initial == obj.m_initial && m_direction == obj.m_direction;
}

// Оператор логического неравенства
bool Ray2D::operator != (Ray2D const & obj) const
{
  return !operator == (obj);
}

// Математическое отрицание (изменяет направление луча)
Ray2D Ray2D::operator - () const
{
  return { -m_direction, m_initial};
}

// Методы

Point2D & Ray2D::initial() { return m_initial; }

Point2D & Ray2D::direction() { return m_direction; }

Point2D const & Ray2D::initial() const { return m_initial; }

Point2D const & Ray2D::direction() const { return m_direction; }

// Замена начальной точки луча
void Ray2D::MoveToPoint (Point2D const & initial)
{
  m_initial = initial;
}

// Измение направления луча
void Ray2D::ChangeDirection (Point2D const & direction)
{
  m_direction = direction;
  Normalize();
}

// Поворот направление луча на degree градусов против часовой стрелки
void Ray2D::RotateDirection (float const degree)
{
  //TODO: обработать деление на 0
  float deg = 180 / PI * atanf(fabs(m_direction.y() / m_direction.x())*PI/180);

  if((m_direction.x() < 0) && (m_direction.y() > 0)) deg += 90;
  else if((m_direction.x() < 0) && (m_direction.y() < 0)) deg += 180;
  else if((m_direction.x() > 0) && (m_direction.y() < 0)) deg += 270;

  m_direction.x() = cosf((degree + deg) * PI / 180);
  m_direction.y() = sinf((degree + deg) * PI / 180);
  Normalize();
}

// Сдвиг начальной точки луча в горизонтальном направлении
void Ray2D::HorizontalMove (float const x)
{
  m_initial.x() += x;
}

// Сдвиг начальной точки луча в вертикальном направлении
void Ray2D::VerticalMove (float const y)
{
  m_initial.y() += y;
}

// Нормирование вектора направления луча
void Ray2D::Normalize()
{
  //TODO: обработать деление на 0
  float norm = sqrtf(m_direction.x()*m_direction.x() + m_direction.y()*m_direction.y());
  m_direction /= norm;
}

// Проверка на равенство с погрешностью
bool Ray2D::EqualWithEps(float v1, float v2) const
{
  return fabs(v1 - v2) < kEps;
}

// Проверка на пересечение луча с отрезком
bool Ray2D::Intersection(Point2D const & p1, Point2D const & p2) const
{
  // TODO: обработать деление на 0
  float k = m_direction.y() / m_direction.x();
  float b = m_initial.y() - k * m_initial.x();

  if (EqualWithEps(p1.x(), p2.x()))
  {
    if ((m_initial.x() <= p1.x() && m_direction.x() > 0
    || m_initial.x() >= p1.x() && m_direction.x() < 0)
    && k * p1.x() + b >= p1.y()
    && k * p1.x() + b <= p2.y())
      return true;
  }
  else
  {
    if (EqualWithEps(m_direction.x(), 0.0f)
    && m_initial.x() >= p1.x()
    && m_initial.x() <= p2.x()
    && (m_initial.y() <= p1.y() && m_direction.y() > 0
    || m_initial.y() >= p1.y() && m_direction.y() < 0))
      return true;

    // TODO: обработать деление на 0
    if ((m_initial.y() <= p1.y() && m_direction.y() > 0
    || m_initial.y() >= p1.y() && m_direction.y() < 0)
    && (p1.y() - b) / k >= p1.x()
    && (p1.y() - b) / k <= p2.x())
      return true;
  }
  return false;
}

// Проверка на пересечение луча и прямоугольника
bool Ray2D::Intersection(Box2D const & obj) const
{
  return Intersection(obj.p1(), Point2D(obj.p1().x(), obj.p2().y()))
         || Intersection(Point2D(obj.p1().x(), obj.p2().y()), obj.p2())
         || Intersection(Point2D(obj.p2().x(), obj.p1().y()), obj.p2())
         || Intersection(obj.p1(), Point2D(obj.p2().x(), obj.p1().y()));
}

//Вывод в поток
std::ostream & operator<<(std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D {initial point: {" << obj.initial().x() << ", " << obj.initial().y() << "}, direction: {" << obj.direction().x() << ", " << obj.direction().y() << "}}";
  return os;
}
