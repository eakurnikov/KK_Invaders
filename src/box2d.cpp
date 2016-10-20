#include "box2d.hpp"
#include <iostream>

// Конструктор с четырьмя координатами
Box2D::Box2D(float const x1, float const y1, float const x2, float const y2)
  : m_leftBottomPoint(x1, y1)
  , m_rightTopPoint(x2, y2)
{
  CheckPoints();
}

// Конструктор с двумя точками.
Box2D::Box2D(Point2D const & leftBottomPoint, Point2D const & rightTopPoint)
  : m_leftBottomPoint(leftBottomPoint)
  , m_rightTopPoint(rightTopPoint)
{
  CheckPoints();
}

// Конструктор с двумя координатами.
Box2D::Box2D(float const x1, float const y1)
  : m_leftBottomPoint(x1, y1)
  , m_rightTopPoint(x1 + 1.0 , y1 + 1.0 )
{
  CheckPoints();
}

// Конструктор с точкой.
Box2D::Box2D(Point2D const & leftBottomPoint)
  : m_leftBottomPoint(leftBottomPoint)
  , m_rightTopPoint(leftBottomPoint.x() + 1.0 , leftBottomPoint.y() + 1.0)
{
  CheckPoints();
}

// Конструктор с параметрами - точкой и двумя сторонами прямоугольника.
Box2D::Box2D(Point2D const & centerPoint, float const xSide, float const ySide)
  : m_leftBottomPoint(centerPoint.x() - xSide / 2.0f, centerPoint.y() - ySide / 2.0f)
  , m_rightTopPoint(centerPoint.x() + xSide / 2.0f, centerPoint.y() + ySide / 2.0f)
{
  CheckPoints();
}

// Конструктор копирования.
Box2D::Box2D(Box2D const & obj)
  : m_leftBottomPoint(obj.leftBottomPoint())
  , m_rightTopPoint(obj.rightTopPoint())
{
  CheckPoints();
}

// Конструктор со списком инициализации из точек.
Box2D::Box2D(std::initializer_list<Point2D> const & lst)
{
  Point2D * arr[] = { & m_leftBottomPoint, & m_rightTopPoint };
  int const count = sizeof(arr) / sizeof(arr[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); i++, ++it)
  {
    *arr[i] = *it;
  }
  CheckPoints();
}

// Конструктор со списком инициализации из координат точек.
Box2D::Box2D(std::initializer_list<float> const & lst)
{
  float * arr[] = { & m_leftBottomPoint.x(), & m_leftBottomPoint.y(), & m_rightTopPoint.x(), & m_rightTopPoint.y() };
  int const count = sizeof(arr) / sizeof(arr[0]);
  auto it = lst.begin();

  for (int i = 0; i < count && it != lst.end(); i++, ++it)
  {
    *arr[i] = *it;
  }
  CheckPoints();
}

// Конструктор перемещения.
Box2D::Box2D(Box2D && obj)
{
  std::swap(m_leftBottomPoint, obj.m_leftBottomPoint);
  std::swap(m_rightTopPoint, obj.m_rightTopPoint);
}

// Изменить левую нижнюю вершину.
void Box2D::SetLeftBottomPoint(Point2D const & leftBottomPoint)
{
  m_rightTopPoint.x() = leftBottomPoint.x() + Width();
  m_rightTopPoint.y() = leftBottomPoint.y() + Height();
  m_leftBottomPoint = leftBottomPoint;
  CheckPoints();
}

// Изменить верхнюю правую вершину.
void Box2D::SetRightTopPoint(Point2D const & rightTopPoint)
{
  m_leftBottomPoint.x() = rightTopPoint.x() - Width();
  m_rightTopPoint.y() = rightTopPoint.y() - Height();
  m_rightTopPoint = rightTopPoint;
  CheckPoints();
}

// Вернуть правую верхнюю вершину.
Point2D const & Box2D::leftBottomPoint() const
{
  return m_leftBottomPoint;
}

// Вернуть левую нижнюю вершину.
Point2D const & Box2D::rightTopPoint() const
{
  return m_rightTopPoint;
}

// Вернуть левую верхнюю вершину.
Point2D const Box2D::leftTopPoint() const
{
  return { m_leftBottomPoint.x(), m_rightTopPoint.y() };
}

// Вернуть правую нижнюю вершину.
Point2D const Box2D::rightBottomPoint() const
{
  return { m_rightTopPoint.x(), m_leftBottomPoint.y() };
}

// Оператор присваивания.
Box2D & Box2D::operator = (Box2D const & obj)
{
  if (this == &obj) return *this;
  m_leftBottomPoint = obj.leftBottomPoint();
  m_rightTopPoint = obj.rightTopPoint();

  return *this;
}

// Оператор перемещения.
Box2D & Box2D::operator = (Box2D && obj)
{
  if (this == &obj) return *this;
  m_leftBottomPoint = std::move(obj.m_leftBottomPoint);
  m_rightTopPoint = std::move(obj.m_rightTopPoint);
  return *this;
}

//Смещение сложением с точкой.
Box2D & Box2D::operator += (Point2D const & obj)
{
  m_leftBottomPoint += obj;
  m_rightTopPoint += obj;

  return *this;
}

//Смещение сложением с числом.
Box2D & Box2D::operator += (float const delta)
{
  m_leftBottomPoint += delta;
  m_rightTopPoint += delta;

  return *this;
}

//Смещение вычитанием точки.
Box2D & Box2D::operator -= (Point2D const & obj)
{
  m_leftBottomPoint -= obj;
  m_rightTopPoint -= obj;

  return *this;
}

//Смещение вычитанием числа.
Box2D & Box2D::operator -= (float const delta)
{
  m_leftBottomPoint -= delta;
  m_rightTopPoint -= delta;

  return *this;
}

//Смещение умножением на точку.
Box2D & Box2D::operator *= (Point2D const & obj)
{
  m_leftBottomPoint *= obj;
  m_rightTopPoint *= obj;

  return *this;
}

//Смещение делением на точку.
Box2D & Box2D::operator /= (Point2D const & obj)
{
  try
  {
    if (obj.x() == 0 || obj.y() == 0) throw std::invalid_argument("Division by zero.");
    m_leftBottomPoint /= obj;
    m_rightTopPoint /= obj;

    return *this;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }
}

//Масштабирование: увеличение.
Box2D & Box2D::operator *= (float const scale)
{
  m_rightTopPoint *= scale;

  return *this;
}

//Масштабирование: уменьшение.
Box2D & Box2D::operator /= (float const scale)
{
  try
  {
    if (scale == 0) throw std::invalid_argument("Division by zero.");
    m_rightTopPoint /= scale;

    return *this;
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }

  return *this;
}

// Математическое отрицание.
Box2D Box2D::operator - () const
{
  return { -m_leftBottomPoint, -m_rightTopPoint };
}

// Вычитание числа.
Box2D Box2D::operator - (float const scale) const
{
  return { m_leftBottomPoint - scale, m_rightTopPoint - scale };
}

// Сложение с числом.
Box2D Box2D::operator + (float const scale) const
{
  return { m_leftBottomPoint + scale, m_rightTopPoint + scale };
}

// Умножение на число.
Box2D Box2D::operator * (float const scale) const
{
  return { m_leftBottomPoint * scale, m_rightTopPoint * scale };
}

// Деление на число.
Box2D Box2D::operator / (float const scale) const
{
  try
  {
    if (scale == 0) throw std::invalid_argument("Division by zero.");
    return {m_leftBottomPoint / scale, m_rightTopPoint / scale};
  }
  catch(std::exception const & ex)
  {
    std::cerr << "Error occurred: " << ex.what() << std::endl;

    return *this;
  }
}

// Оператор логического равенства.
bool Box2D::operator == (Box2D const & obj) const
{
  return (m_leftBottomPoint == obj.m_leftBottomPoint) && (m_rightTopPoint == obj.m_rightTopPoint);
}

// Оператор логического неравенства.
bool Box2D::operator != (Box2D const & obj) const
{
  return ! operator == (obj);
}

// Установить центр.
void Box2D::SetCenter(Point2D const & obj)
{
  m_leftBottomPoint = { obj.x() - Width() / 2.0f, obj.y() - Height() / 2.0f };
  m_rightTopPoint = { obj.x() + Width() / 2.0f, obj.y() + Height() / 2.0f };
}

// Вернуть центр.
Point2D Box2D::GetCenter() const
{
  Point2D p = { (m_leftBottomPoint.x() + m_rightTopPoint.x()) / 2.0f , (m_leftBottomPoint.y() + m_rightTopPoint.y()) / 2.0f };
  return p;
}

// Вернуть высоту.
float Box2D::Height() const
{
  return m_rightTopPoint.y() - m_leftBottomPoint.y();
}

// Вернуть ширину.
float Box2D::Width() const
{
  return m_rightTopPoint.x() - m_leftBottomPoint.x();
}

// Вернуть периметр
float Box2D::Perimeter() const
{
  return 2.0f * (m_rightTopPoint.x() - m_leftBottomPoint.x()) + 2 * (m_rightTopPoint.y() - m_leftBottomPoint.y());
}

// Вернуть площадь
float Box2D::Area() const
{
  return (m_rightTopPoint.x() - m_leftBottomPoint.x())*(m_rightTopPoint.y() - m_leftBottomPoint.y());
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
Point2D Box2D::operator [] (unsigned int const index) const
{
  if (index >= 2)
  {
    return {0.0, 0,0};
  }
  else
  {
    return index == 0 ? m_leftBottomPoint : m_rightTopPoint;
  }
}

// Проверка корректности задания точек прямоугольника.
void Box2D::CheckPoints()
{
  Point2D p1 = Point2D(std::min(m_leftBottomPoint.x(), m_rightTopPoint.x()), std::min(m_leftBottomPoint.y(), m_rightTopPoint.y()));
  Point2D p2 = Point2D(std::max(m_leftBottomPoint.x(), m_rightTopPoint.x()), std::max(m_leftBottomPoint.y(), m_rightTopPoint.y()));
  m_leftBottomPoint = p1;
  m_rightTopPoint = p2;
}

// Проверка, лежит ли точка в данном прямоугольнике.
bool Box2D::IsPointInBox(Point2D const & obj) const
{
  return obj > m_leftBottomPoint && obj < m_rightTopPoint;
}

// Проверка, пересекается ли прямоугольник с данным прямоугольником.
bool Box2D::IsBoxesIntersect(Box2D const & obj) const
{
  return this->IsPointInBox(obj.leftBottomPoint()) ||
         this->IsPointInBox(obj.rightTopPoint()) ||
         this->IsPointInBox(obj.leftTopPoint()) ||
         this->IsPointInBox(obj.rightBottomPoint());
}

// Проверка на равенство с эпсилон #1.
bool Box2D::EqualWithEps(float const a, float const b) const
{
  return fabs(a - b) < kEps;
}

// Проверка на равенство с эпсилон #2.
bool Box2D::EqualWithEps(Point2D const & p1, Point2D const & p2) const
{
  return (fabs(p1.x() - p2.x())) < kEps && (fabs(p1.y() - p2.y()) < kEps);
}

// Вывод в поток
std::ostream & operator << (std::ostream & os, Box2D const & obj)
{
  os << "Box2D {" << obj.leftBottomPoint() << ", " << obj.rightTopPoint() << "}";
  return os;
}
