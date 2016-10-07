#include "box2d.hpp"
#include <iostream>

//Конструктор с двумя координатами
Box2D::Box2D(float const x2, float const y2)
  : m_p2(x2, y2)
{
  CheckPoints();
}

//Конструктор с четырьмя координатами
Box2D::Box2D(float const x1, float const y1, float const x2, float const y2)
  : m_p1(x1, y1)
  , m_p2(x2, y2)
{
  CheckPoints();
}

//Конструктор с параметрами - точками.
Box2D::Box2D(Point2D p1, Point2D p2)
  : m_p1(p1)
  , m_p2(p2)
{
  CheckPoints();
}

//Конструктор с параметром - точкой.
Box2D::Box2D(Point2D p1)
  : m_p2(p1)
{
  CheckPoints();
}

//Конструктор с параметрами - точкой и двумя сторонами прямоугольника.
Box2D::Box2D(Point2D p1, float xSide, float ySide)
  : m_p1(p1)
  , m_p2(p1.x() + xSide, p1.y() + ySide)
{
  CheckPoints();
}

//Конструктор копирования.
Box2D::Box2D(Box2D const & obj)
  : m_p1(obj.p1())
  , m_p2(obj.p2())
{
  CheckPoints();
}

//Конструктор со списком инициализации из точек.
Box2D::Box2D(std::initializer_list<Point2D> const & lst)
{
  Point2D * arr[] = { & m_p1, & m_p2 };
  int const count = sizeof(arr) / sizeof(arr[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); i++, ++it)
  {
    *arr[i] = *it;
  }
  CheckPoints();
}

//Конструктор со списком инициализации из координат точек.
Box2D::Box2D(std::initializer_list<float> const & lst)
{
  float * arr[] = { & m_p1.x(), & m_p1.y(), & m_p2.x(), & m_p2.y() };
  int const count = sizeof(arr) / sizeof(arr[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); i++, ++it)
  {
    *arr[i] = *it;
  }
  CheckPoints();
}

// Вернуть правую верхнюю вершину.
Point2D & Box2D::p1()
{
  return m_p1;
}

// Вернуть левую нижнюю вершину.
Point2D & Box2D::p2()
{
  return m_p2;
}

// Вернуть правую верхнюю вершину.
Point2D const & Box2D::p1() const
{
  return m_p1;
}

// Вернуть левую нижнюю вершину.
Point2D const & Box2D::p2() const
{
  return m_p2;
}

// Вернуть левую верхнюю вершину.
Point2D const & Box2D::left_top_point() const
{
  return { m_p1.x(), m_p2.y() };
}

// Вернуть правую нижнюю вершину.
Point2D const & Box2D::right_bottom_point() const
{
  return { m_p2.x(), m_p1.y() };
}

// Оператор присваивания #1.
Box2D & Box2D::operator = (Box2D const & obj)
{
  m_p1 = obj.p1();
  m_p2 = obj.p2();

  return *this;
}

//Смещение сложением с точкой.
Box2D & Box2D::operator += (Point2D const & obj)
{
  m_p1 += obj;
  m_p2 += obj;

  return *this;
}

//Смещение сложением с числом.
Box2D & Box2D::operator += (float delta)
{
  m_p1 += delta;
  m_p2 += delta;

  return *this;
}

//Смещение вычитанием точки.
Box2D & Box2D::operator -= (Point2D const & obj)
{
  m_p1 -= obj;
  m_p2 -= obj;

  return *this;
}

//Смещение вычитанием числа.
Box2D & Box2D::operator -= (float delta)
{
  m_p1 -= delta;
  m_p2 -= delta;

  return *this;
}

//Смещение умножением на точку.
Box2D & Box2D::operator *= (Point2D const & obj)
{
  m_p1 *= obj;
  m_p2 *= obj;

  return *this;
}

//Смещение делением на точку.
Box2D & Box2D::operator /= (Point2D const & obj)
{
  try
  {
    m_p1 /= obj;
    m_p2 /= obj;

    return *this;
  }
  catch(const std::exception & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }
}

//Масштабирование: увеличение.
Box2D & Box2D::operator *= (float scale)
{
  m_p2 *= scale;

  return *this;
}

//Масштабирование: уменьшение.
Box2D & Box2D::operator /= (float scale)
{
  try
  {
    m_p2 /= scale;

    return *this;
  }
  catch(const std::exception & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }

  return *this;
}

// Математическое отрицание.
Box2D Box2D::operator - () const
{
  return { -m_p1, -m_p2 };
}

// Вычитание числа.
Box2D Box2D::operator - (float scale) const
{
  return { m_p1 - scale, m_p2 - scale };
}

// Сложение с числом.
Box2D Box2D::operator + (float scale) const
{
  return { m_p1 + scale, m_p2 + scale };
}

// Умножение на число.
Box2D Box2D::operator * (float scale)
{
  return { m_p1 * scale, m_p2 * scale };
}

// Деление на число.
Box2D Box2D::operator / (float scale)
{
  try
  {
    return {m_p1 / scale, m_p2 / scale};
  }
  catch(const std::exception & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }
}

// Оператор логического равенства.
bool Box2D::operator == (Box2D const & obj) const
{
  return (m_p1 == obj.m_p1) && (m_p2 == obj.m_p2);
}

// Оператор логического неравенства.
bool Box2D::operator != (Box2D const & obj) const
{
  return ! operator == (obj);
}

// Вернуть центр.
Point2D Box2D::GetCenter() const
{
  Point2D p = { (m_p1.x() + m_p2.x()) / 2 , (m_p1.y() + m_p2.y()) / 2 };
  return p;
}

// Вернуть высоту.
float Box2D::Height() const
{
  return m_p2.y() - m_p1.y();
}

// Вернуть ширину.
float Box2D::Width() const
{
  return m_p2.x() - m_p1.x();
}

// Вернуть периметр
float Box2D::Perimeter() const
{
  return 2 * (m_p2.x() - m_p1.x()) + 2 * (m_p2.y() - m_p1.y());
}

// Вернуть площадь
float Box2D::Area() const
{
  return (m_p2.x() - m_p1.x())*(m_p2.y() - m_p1.y());
}

// Оператор меньше.
bool Box2D::operator < (Box2D const & obj) const
{
  return this->Area() < obj.Area();
}

// Оператор меньше равно.
bool Box2D::operator <= (Box2D const & obj) const
{
  return Area() <= obj.Area();
}

// Оператор больше.
bool Box2D::operator > (Box2D const & obj) const
{
  return Area() > obj.Area();
}

// Оператор больше равно.
bool Box2D::operator >= (Box2D const & obj) const
{
  return Area() >= obj.Area();
}

// Переопределение оператора [].
Point2D Box2D::operator [] (unsigned int index) const
{
  if (index >= 2)
  {
  return {0.0, 0,0};
  }
  else
  {
  return index == 0 ? m_p1 : m_p2;
  }
}

// Проверка корректности задания точек прямоугольника.
void Box2D::CheckPoints()
{
  if(m_p2 < m_p1)
  {
  Point2D buffer = m_p1;
  m_p1 = m_p2;
  m_p2 = buffer;
  }
}

// Проверка, лежит ли точка в данном прямоугольнике.
bool Box2D::IsPointInBox(Point2D const & obj) const
{
  return obj > m_p1 && obj < m_p2;
}

// Проверка, пересекается ли прямоугольник с данным прямоугольником.
bool Box2D::IsBoxesIntersect(Box2D const & obj) const
{
  return this->IsPointInBox(obj.p1()) ||
         this->IsPointInBox(obj.p2()) ||
         this->IsPointInBox(obj.left_top_point()) ||
         this->IsPointInBox(obj.right_bottom_point());
}

// Проверка на равенство с эпсилон #1.
bool Box2D::EqualWithEps(float a, float b) const
{
  return fabs(a - b) < kEps;
}

// Проверка на равенство с эпсилон #2.
bool Box2D::EqualWithEps(Point2D const & a, Point2D const & b) const
{
  return fabs(a.x() - b.x())*fabs(a.y() - b.y()) < kEps;
}

// Вывод в поток
std::ostream & operator << (std::ostream & os, Box2D const & obj)
{
  os << "Box2D {" << obj.p1() << ", " << obj.p2() << "}";
  return os;
}
