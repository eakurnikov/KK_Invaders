#include "ray2d.hpp"
#include <iostream>

#define M_PI 3.14159265358979323846

// Конструкторы

// Конструктор с заданием двух координат, определяющих направление луча
Ray2D::Ray2D(float const directionX, float const directionY)
  : m_direction(directionX, directionY)
{
  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Конструктор с заданием четырех координат, определяющих направление луча и его начало
Ray2D::Ray2D( float const directionX, float const directionY, float const initialX, float const initialY)
  : m_direction(directionX, directionY)
  , m_initial(initialX, initialY)
{
  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Конструктор с заданием точки, определяющей направление луча
Ray2D::Ray2D(Point2D const & direction)
  : m_direction(direction)
{
  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Конструктор с заданием двух точек, определяющих направление луча и его начало
Ray2D::Ray2D(Point2D const & direction, Point2D const & initial)
  : m_direction(direction)
  , m_initial(initial)
{
  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
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

  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Конструктор со списком иниациализации
Ray2D::Ray2D(std::initializer_list<float> const & lst)
{
  float * vals[] = { &m_direction.x(), &m_direction.y(), &m_initial.x(), &m_initial.y() };
  int const count = sizeof(vals) / sizeof(vals[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); ++i, ++it)
  {
    *vals[i] = *it;
  }

  try
  {
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Конструктор перемещения
Ray2D::Ray2D(Ray2D && obj)
{
  std::swap(m_initial, obj.m_initial);
  std::swap(m_direction, obj.m_direction);
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

// Оператор перемещения
Ray2D & Ray2D::operator = (Ray2D && obj)
{
  if (this == &obj) return *this;
  std::swap(m_initial, obj.m_initial);
  std::swap(m_direction, obj.m_direction);
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
  return {-m_direction, m_initial};
}

// Методы

// Изменить начало луча
void Ray2D::SetInitial(Point2D const & initial)
{
  m_initial = initial;
  Normalize();
}

// Изменить направления луча
void Ray2D::SetDirection (Point2D const & direction)
{
  m_direction = direction;
  Normalize();
}

Point2D const & Ray2D::initial() const
{
  return m_initial;
}

Point2D const & Ray2D::direction() const
{
  return m_direction;
}

// Поворот направление луча на degree градусов против часовой стрелки
void Ray2D::RotateDirection (float const degree)
{
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(m_direction.x(), 0.0f)) throw std::invalid_argument("Division by zero.");
    float deg = 180 / M_PI * atanf(fabs(m_direction.y() / m_direction.x()) * M_PI / 180);

    if((m_direction.x() < 0.0f) && (m_direction.y() > 0.0f)) deg += 90;
    else if((m_direction.x() < 0.0f) && (m_direction.y() < 0.0f)) deg += 180;
    else if((m_direction.x() > 0.0f) && (m_direction.y() < 0.0f)) deg += 270;

    m_direction.x() = cosf((degree + deg) * M_PI / 180);
    m_direction.y() = sinf((degree + deg) * M_PI / 180);
    Normalize();
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Сдвиг начальной точки луча в горизонтальном направлении
void Ray2D::HorizontalMove (float const x)
{
  m_initial.x() += x;
  m_direction.x() += x;
}

// Сдвиг начальной точки луча в вертикальном направлении
void Ray2D::VerticalMove (float const y)
{
  m_initial.y() += y;
  m_direction.y() += y;
}

// Нормирование вектора направления луча
void Ray2D::Normalize()
{
  float norm = sqrtf((m_direction.x() - m_initial.x()) * (m_direction.x() - m_initial.x()) + (m_direction.y() - m_initial.y()) * (m_direction.y() - m_initial.y()));
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(norm, 0.0f)) throw std::invalid_argument("Division by zero.");
    m_direction = (m_direction - m_initial) / norm + m_initial;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Проверка на пересечение луча с отрезком
bool Ray2D::Intersection(Point2D const & p1, Point2D const & p2) const
{
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(m_direction.x(), 0.0f)) throw std::invalid_argument("Division by zero.");
    float k = m_direction.y() / m_direction.x();
    float b = m_initial.y() - k * m_initial.x();

    if (OperationsWithEpsilon::EqualWithEps(p1.x(), p2.x()))
    {
      if ((m_initial.x() <= p1.x() && m_direction.x() > 0.0f || m_initial.x() >= p1.x() && m_direction.x() < 0.0f)
          && k * p1.x() + b >= p1.y() && k * p1.x() + b <= p2.y())
        return true;
    }
    else
    {
      if (OperationsWithEpsilon::EqualWithEps(m_direction.x(), 0.0f) && m_initial.x() >= p1.x() && m_initial.x() <= p2.x()
          && (m_initial.y() <= p1.y() && m_direction.y() > 0.0f || m_initial.y() >= p1.y() && m_direction.y() < 0.0f))
        return true;

      if (OperationsWithEpsilon::EqualWithEps(k, 0.0f)) throw std::invalid_argument("Division by zero.");

      if ((m_initial.y() <= p1.y() && m_direction.y() > 0.0f || m_initial.y() >= p1.y() && m_direction.y() < 0.0f)
          && (p1.y() - b) / k >= p1.x() && (p1.y() - b) / k <= p2.x())
        return true;
    }
  return false;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Проверка на пересечение луча и прямоугольника
bool Ray2D::Intersection(Box2D const & obj) const
{
  return Intersection(obj.leftBottomPoint(), Point2D(obj.leftBottomPoint().x(), obj.rightTopPoint().y()))
         || Intersection(Point2D(obj.leftBottomPoint().x(), obj.rightTopPoint().y()), obj.rightTopPoint())
         || Intersection(Point2D(obj.rightTopPoint().x(), obj.leftBottomPoint().y()), obj.rightTopPoint())
         || Intersection(obj.leftBottomPoint(), Point2D(obj.rightTopPoint().x(), obj.leftBottomPoint().y()));
}

//Вывод в поток
std::ostream & operator<<(std::ostream & os, Ray2D const & obj)
{
  os << "Ray2D {initial point: {" << obj.initial().x() << ", " << obj.initial().y() << "}, direction: {" << obj.direction().x() << ", " << obj.direction().y() << "}}";
  return os;
}
