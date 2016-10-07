#pragma once

#include "point2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>


class Box2D
{
public:
  //Разрешаем конструктор по умолчанию.
  Box2D() = default;

  //Конструктор с двумя координатами
  Box2D(float const x2, float const y2);

  //Конструктор с четырьмя координатами
  Box2D(float const x1, float const y1, float const x2, float const y2);

  //Конструктор с параметром - точкой.
  Box2D(Point2D p1);

  //Конструктор с параметрами - точками.
  Box2D(Point2D p1, Point2D p2);

  //Конструктор с параметрами - точкой и двумя сторонами прямоугольника.
  Box2D(Point2D p1, float xSide, float ySide);

  //Конструктор копирования.
  Box2D(Box2D const & obj);

  //Конструктор со списком инициализации из точек.
  Box2D(std::initializer_list<Point2D> const & lst);

  //Конструктор со списком инициализации из координат точек.
  Box2D(std::initializer_list<float> const & lst);

  Point2D & p1();

  Point2D & p2();

  Point2D const & p1() const;

  Point2D const & p2() const;

  Point2D const & left_top_point() const;

  Point2D const & right_bottom_point() const;

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj);

  //Смещение сложением с точкой.
  Box2D & operator += (Point2D const & obj);

  //Смещение сложением с числом.
  Box2D & operator += (float delta);

  //Смещение вычитанием точки.
  Box2D & operator -= (Point2D const & obj);

  //Смещение вычитанием числа.
  Box2D & operator -= (float delta);

  //Смещение умножением на точку.
  Box2D & operator *= (Point2D const & obj);

  //Смещение делением на точку.
  Box2D & operator /= (Point2D const & obj);

  //Масштабирование: увеличение.
  Box2D & operator *= (float scale);

  //Масштабирование: уменьшение.
  Box2D & operator /= (float scale);

  // Математическое отрицание.
  Box2D operator - () const;

  // Вычитание числа.
  Box2D operator - (float scale) const;

  // Сложение с числом.
  Box2D operator + (float scale) const;

  // Умножение на число.
  Box2D operator * (float scale);

  // Деление на число.
  Box2D operator / (float scale);

  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const;

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const;

  // Вернуть центр.
  Point2D GetCenter() const;

  // Вернуть высоту.
  float Height() const;

  // Вернуть ширину.
  float Width() const;

  // Вернуть периметр
  float Perimeter() const;

  // Вернуть площадь
  float Area() const;

  // Оператор меньше.
  bool operator < (Box2D const & obj) const;

  // Оператор меньше равно.
  bool operator <= (Box2D const & obj) const;

  // Оператор больше.
  bool operator > (Box2D const & obj) const;

  // Оператор больше равно.
  bool operator >= (Box2D const & obj) const;

  // Переопределение оператора [].
  Point2D operator [] (unsigned int index) const;

  // Проверка, лежит ли точка в данном прямоугольнике.
  bool IsPointInBox(Point2D const & obj) const;

  // Проверка, пересекается ли прямоугольник с данным прямоугольником.
  bool IsBoxesIntersect(Box2D const & obj) const;

private:
  // Левая нижняя точка
  Point2D m_p1 = { 0.0, 0.0 };

  // Правая верхняя точка
  Point2D m_p2 = { 0.0, 0.0 };

  // Проверка корректности задания точек прямоугольника.
  void CheckPoints();

  // Проверка на равенство с эпсилон #1.
  bool EqualWithEps(float a, float b) const;

  // Проверка на равенство с эпсилон #2.
  bool EqualWithEps(Point2D const & a, Point2D const & b) const;
};

std::ostream & operator << (std::ostream & os, Box2D const & obj);
