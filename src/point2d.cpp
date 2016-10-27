#include "Point2D.hpp"
#include <iostream>

// Конструктор с параметрами.
Point2D::Point2D(float const x, float const y)
  : m_x(x)
  , m_y(y)
{}

// Конструктор копирования.
Point2D::Point2D(Point2D const & obj)
  : m_x(obj.x())
  , m_y(obj.y())
{}

// Конструктор со списком инициализации.
Point2D::Point2D(std::initializer_list<float> const & lst)
{
  float * arr[] = { &m_x, &m_y };
  int const count = sizeof(arr) / sizeof(arr[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); i++, ++it)
  {
    *arr[i] = *it;
  }
}

// Конструктор перемещения.
Point2D::Point2D(Point2D && obj)
{
  std::swap(m_x, obj.x());
  std::swap(m_y, obj.y());
}

float & Point2D::x() { return m_x; }

float & Point2D::y() { return m_y; }

float const & Point2D::x() const { return m_x; }

float const & Point2D::y() const { return m_y; }

// Оператор присваивания.
Point2D & Point2D::operator = (Point2D const & obj)
{
  if (this == &obj) return *this;
  m_x = obj.x();
  m_y = obj.y();

  return *this;
}

// Оператор перемещения.
Point2D & Point2D::operator = (Point2D && obj)
{
  if (this == &obj) return *this;
  std::swap(m_x, obj.x());
  std::swap(m_y, obj.y());
  return *this;
}

// Смещение сложением с точкой.
Point2D & Point2D::operator += (Point2D const & obj)
{
  m_x += obj.x();
  m_y += obj.y();

  return *this;
}

// Смещение сложением с числом.
Point2D & Point2D::operator += (float const delta)
{
  m_x += delta;
  m_y += delta;

  return *this;
}

// Смещение вычитанием точки.
Point2D & Point2D::operator -= (Point2D const & obj)
{
  m_x -= obj.x();
  m_y -= obj.y();

  return *this;
}

// Смещение вычитанием числа.
Point2D & Point2D::operator -= (float const delta)
{
  m_x -= delta;
  m_y -= delta;

  return *this;
}

// Смещение умножением на точку.
Point2D & Point2D::operator *= (Point2D const & obj)
{
  m_x *= obj.x();
  m_y *= obj.y();

  return *this;
}

// Смещение умножением на число.
Point2D & Point2D::operator *= (float const scale)
{
  m_x *= scale;
  m_y *= scale;

  return *this;
}

// Смещение делением на точку.
Point2D & Point2D::operator /= (Point2D const & obj)
{
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(obj.x(), 0.0f) || OperationsWithEpsilon::EqualWithEps(obj.y(), 0.0f)) throw std::invalid_argument("Division by zero.");
    m_x /= obj.x();
    m_y /= obj.y();

    return *this;
  }

  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Смещение делением на число.
Point2D & Point2D::operator /= (float const scale)
{
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(scale, 0.0f)) throw std::invalid_argument("Division by zero.");
    m_x /= scale;
    m_y /= scale;

    return *this;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Математическое отрицание.
Point2D Point2D::operator - () const
{
  return { -m_x, -m_y };
}

// Вычитание точки.
Point2D Point2D::operator - (Point2D const & obj) const
{
  return { m_x - obj.x(), m_y - obj.y() };
}

// Вычитание числа.
Point2D Point2D::operator - (float const scale) const
{
  return { m_x - scale, m_y - scale };
}

// Сложение с точкой.
Point2D Point2D::operator + (Point2D const & obj) const
{
  return { m_x + obj.x(), m_y + obj.y() };
}

// Сложение с числом.
Point2D Point2D::operator + (float const scale) const
{
  return { m_x + scale, m_y + scale };
}

// Умножение на число.
Point2D Point2D::operator * (float const scale) const
{
  return { m_x * scale, m_y * scale };
}

// Деление на число.
Point2D Point2D::operator / (float const scale) const
{
  try
  {
    if (OperationsWithEpsilon::EqualWithEps(scale, 0.0f)) throw std::invalid_argument("Division by zero.");
    return { m_x / scale, m_y / scale };
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;
    throw;
  }
}

// Оператор логического равенства.
bool Point2D::operator == (Point2D const & obj) const
{
  return OperationsWithEpsilon::EqualWithEps(m_x, obj.x()) && OperationsWithEpsilon::EqualWithEps(m_y, obj.y());
}

// Оператор логического неравенства.
bool Point2D::operator != (Point2D const & obj) const
{
  return ! operator == (obj);
}

// Оператор меньше.
bool Point2D::operator < (Point2D const & obj) const
{
  return m_x < obj.x() && m_y < obj.y();
}

// Оператор меньше равно.
bool Point2D::operator <= (Point2D const & obj) const
{
  return m_x <= obj.x() && m_y <= obj.y();
}

// Оператор больше.
bool Point2D::operator > (Point2D const & obj) const
{
  return m_x > obj.x() && m_y > obj.y();
}

// Оператор больше равно.
bool Point2D::operator >= (Point2D const & obj) const
{
  return m_x >= obj.x() && m_y >= obj.y();
}

// Переопределение оператора [].
float Point2D::operator [] (unsigned int index) const
{
  if (index >= 2)
  {
    return 0.0;
  }
  else
  {
    return index == 0 ? m_x : m_y;
  }
}

// Внутренняя сущность для вычисления хэша
size_t Point2D::Hash::operator () (Point2D const & p) const
{
  auto hasher = std::hash<float>();
  return (hasher(p.x()) ^ (hasher(p.y()) << 1));
}

std::ostream & operator << (std::ostream & os, Point2D const & obj)
{
  os << "Point2D {" << obj.x() << ", " << obj.y() << "}";
  return os;
}
