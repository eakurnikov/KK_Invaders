#pragma once

#include "operationswithepsilon.h"
#include "point2d.hpp"
#include <cmath>
#include <initializer_list>
#include <functional>
#include <ostream>
#include <iostream>

class Box2D
{
public:

  // Разрешаем конструктор по умолчанию.
  Box2D() = default;

  // Конструктор с четырьмя координатами
  Box2D(float const x1, float const y1, float const x2, float const y2);

  // Конструктор с двумя точками.
  Box2D(Point2D const & leftBottomPoint, Point2D const & rightTopPoint);

  // Конструктор с двумя координатами
  Box2D(float const x1, float const y1);

  // Конструктор с точкой.
  Box2D(Point2D const & leftBottomPoint);

  // Конструктор с параметрами - точкой и двумя сторонами прямоугольника.
  Box2D(Point2D const & centerPoint, float const xSide, float const ySide);

  // Конструктор копирования.
  Box2D(Box2D const & obj);

  // Конструктор со списком инициализации из точек.
  Box2D(std::initializer_list<Point2D> const & lst);

  // Конструктор со списком инициализации из координат точек.
  Box2D(std::initializer_list<float> const & lst);

  // Конструктор перемещения.
  Box2D(Box2D && obj);

  // Изменить левую нижнюю вершину.
  void SetLeftBottomPoint(Point2D const & leftBottomPoint);

  // Изменить правую верхнюю вершину.
  void SetRightTopPoint(Point2D const & rightTopPoint);

  Point2D const & leftBottomPoint() const;

  Point2D const & rightTopPoint() const;

  Point2D const leftTopPoint() const;

  Point2D const rightBottomPoint() const;

  // Оператор присваивания.
  Box2D & operator = (Box2D const & obj);

  // Оператор перемещения.
  Box2D & operator = (Box2D && obj);

  // Смещение сложением с точкой.
  Box2D & operator += (Point2D const & obj);

  // Смещение сложением с числом.
  Box2D & operator += (float const delta);

  // Смещение вычитанием точки.
  Box2D & operator -= (Point2D const & obj);

  // Смещение вычитанием числа.
  Box2D & operator -= (float const delta);

  // Смещение умножением на точку.
  Box2D & operator *= (Point2D const & obj);

  // Смещение делением на точку.
  Box2D & operator /= (Point2D const & obj);

  // Масштабирование: увеличение.
  Box2D & operator *= (float const scale);

  // Масштабирование: уменьшение.
  Box2D & operator /= (float const scale);

  // Математическое отрицание.
  Box2D operator - () const;

  // Вычитание числа.
  Box2D operator - (float const scale) const;

  // Сложение с числом.
  Box2D operator + (float const scale) const;

  // Умножение на число.
  Box2D operator * (float const scale) const;

  // Деление на число.
  Box2D operator / (float const scale) const;

  // Оператор логического равенства.
  bool operator == (Box2D const & obj) const;

  // Оператор логического неравенства.
  bool operator != (Box2D const & obj) const;

  // Установить центр.
  void SetCenter(Point2D const & obj);

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
  Point2D operator [] (unsigned int const index) const;

  // Проверка, лежит ли точка в данном прямоугольнике.
  bool IsPointInBox(Point2D const & obj) const;

  // Проверка, пересекается ли прямоугольник с данным прямоугольником.
  bool IsBoxesIntersect(Box2D const & obj) const;

private:

  // Левая нижняя точка
  Point2D m_leftBottomPoint = {0.0, 0.0};

  // Правая верхняя точка
  Point2D m_rightTopPoint = {0.0, 0.0};

  // Проверка корректности задания точек прямоугольника.
  void CheckPoints();

  // Проверка на равенство с эпсилон.
  bool EqualWithEps(Point2D const & a, Point2D const & b) const;
};

std::ostream & operator << (std::ostream & os, Box2D const & obj);
