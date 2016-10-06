#pragma once

#include <cmath>
//#include <math.h>
#include <initializer_list>
#include <functional>
#include <ostream>

float const kEps = 1e-5;

class Point2D
{
public:
  // Разрешаем конструирование по умолчанию.
  Point2D() = default;

  // Конструктор с параметрами.
  Point2D(float x, float y);

  // Конструктор копирования.
  Point2D(Point2D const & obj);

  // Конструктор со списком инициализации.
  Point2D(std::initializer_list<float> const & lst);

  float & x();

  float & y();

  float const & x() const;

  float const & y() const;

  // Оператор присваивания.
  Point2D & operator = (Point2D const & obj);

  // Смещение сложением с точкой.
  Point2D & operator += (Point2D const & obj);

  // Смещение сложением с числом.
  Point2D & operator += (float delta);

  // Смещение вычитанием точки.
  Point2D & operator -= (Point2D const & obj);

  // Смещение вычитанием числа.
  Point2D & operator -= (float delta);

  // Смещение умножением на точку.
  Point2D & operator *= (Point2D const & obj);

  // Смещение умножением на число.
  Point2D & operator *= (float scale);

  // Смещение делением на точку.
  Point2D & operator /= (Point2D const & obj);

  // Смещение делением на число.
  Point2D & operator /= (float scale);

  // Математическое отрицание.
  Point2D operator - () const;

  // Вычитание точки.
  Point2D operator - (Point2D const & obj) const;

  // Вычитание числа.
  Point2D operator - (float scale) const;

  // Сложение с точкой.
  Point2D operator + (Point2D const & obj) const;

  // Сложение с числом.
  Point2D operator + (float scale) const;

  // Умножение на число.
  Point2D operator * (float scale);

  // Деление на число.
  Point2D operator / (float scale);

  // Оператор логического равенства.
  bool operator == (Point2D const & obj) const;

  // Оператор логического неравенства.
  bool operator != (Point2D const & obj) const;

  // Оператор меньше.
  bool operator < (Point2D const & obj) const;

  // Оператор меньше равно.
  bool operator <= (Point2D const & obj) const;

  // Оператор больше.
  bool operator > (Point2D const & obj) const;

  // Оператор больше равно.
  bool operator >= (Point2D const & obj) const;

  // Переопределение оператора [].
  float operator [] (unsigned int index) const;

  // Внутренняя сущность для вычисления хэша.
  struct Hash
  {
    size_t operator()(Point2D const & p) const;
  };

private:

  float m_x = 0.0f;
  float m_y = 0.0f;

  // Проверка на равенство с эпсилон.
  bool EqualWithEps(float a, float b) const;
};

std::ostream & operator << (std::ostream & os, Point2D const & obj);
