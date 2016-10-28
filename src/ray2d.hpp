#pragma once

#include "operationswithepsilon.h"
#include "point2d.hpp"
#include "box2d.hpp"
#include <initializer_list>
#include <functional>
#include <ostream>
#include <cmath>

class Ray2D
{
public:
  // Конструкторы

  // Конструирование по умолчанию
  Ray2D() = default;

  // Конструктор с заданием двух координат, определяющих направление луча
  Ray2D(float const direction_x, float const direction_y);

  // Конструктор с заданием четырех координат, определяющих направление луча и его начало
  Ray2D(float const direction_x, float const direction_y, float const initial_x, float const initial_y);

  // Конструктор с заданием точки, определяющей направление луча
  Ray2D(Point2D const & direction);

  // Конструктор с заданием двух точек, определяющих направление луча и его начало
  Ray2D(Point2D const & direction, Point2D const & initial);

  // Конструктор с заданием параметров на основе сущестующего луча
  Ray2D(Ray2D const & obj);

  // Конструктор со списком иниациализации
  Ray2D(std::initializer_list<Point2D> const & lst);

  // Конструктор со списком иниациализации
  Ray2D(std::initializer_list<float> const & lst);

  // Конструктор перемещения
  Ray2D(Ray2D && obj);

  // Оператор перемещения
  Ray2D & operator = (Ray2D && obj);

  // Методы

  // Изменить начало луча
  void SetInitial(Point2D const & initial);

  // Изменить направления луча
  void SetDirection (Point2D const & direction);

  Point2D const & initial() const;

  Point2D const & direction() const;

  float const GetDirection() const;

  // Поворот направление луча на degree градусов против часовой стрелки
  void RotateDirection (float const degree);

  // Сдвиг начальной точки луча в горизонтальном направлении
  void HorizontalMove (float const x);

  // Сдвиг начальной точки луча в вертикальном направлении
  void VerticalMove (float const y);

  // Проверка на пересечение луча с отрезком
  bool Intersection(Point2D const & p1, Point2D const & p2) const;

  // Проверка пересечения с прямоугольником
  bool Intersection(Box2D const & box) const;

  // Операторы

  // Оператор присваивания
  Ray2D & operator = (Ray2D const & obj);

  // Оператор логического равенства
  bool operator == (Ray2D const & obj) const;

   // Оператор логического неравенства
  bool operator != (Ray2D const & obj) const;

  // Математическое отрицание
  Ray2D operator - () const;

private:

  // Методы

  // Нормирование вектора направления луча
  void Normalize();

  // Переменные

  // Направление луча
  Point2D m_direction = { 1.0f, 0.0f };

  // Начало луча
  Point2D m_initial = { 0.0f, 0.0f };
};

// Вывод в поток
std::ostream & operator<<(std::ostream & os, Ray2D const & obj);
