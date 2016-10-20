#include "gtest/gtest.h"
#include "ray2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(ray2d_test, test_construction)
{
  // Тестирование конструкторов

  // Конструктор по умолчанию
  Ray2D r0;
  EXPECT_EQ(r0.initial().x(), 0.0f);
  EXPECT_EQ(r0.initial().y(), 0.0f);
  EXPECT_EQ(r0.direction().x(), 1.0f);
  EXPECT_EQ(r0.direction().y(), 0.0f);

  // Конструктор с заданием двух координат, определяющих направление луча
  Ray2D r1 = Ray2D(0.0f, 2.0f);
  EXPECT_EQ(r1.initial().x(), 0.0f);
  EXPECT_EQ(r1.initial().y(), 0.0f);
  EXPECT_EQ(r1.direction().x(), 0.0f);
  EXPECT_EQ(r1.direction().y(), 1.0f);

  // Конструктор с заданием четырех координат, определяющих начало луча и его направление
  Ray2D r2 = Ray2D(2.0f, 4.0f, 2.0f, 2.0f);
  EXPECT_EQ(r2.initial().x(), 2.0f);
  EXPECT_EQ(r2.initial().y(), 2.0f);
  EXPECT_EQ(r2.direction().x(), 2.0f);
  EXPECT_EQ(r2.direction().y(), 3.0f);

  // Конструктор с заданием точки, определяющей направление луча
  Ray2D r3 = Ray2D(Point2D(0.0f, 2.0f));
  EXPECT_EQ(r3.initial().x(), 0.0f);
  EXPECT_EQ(r3.initial().y(), 0.0f);
  EXPECT_EQ(r3.direction().x(), 0.0f);
  EXPECT_EQ(r3.direction().y(), 1.0f);

  // Конструктор с заданием двух точек, определяющих начало луча и его направление
  Point2D p1 = { 0.0f, 3.0f };
  Point2D p2 = { 0.0f, -1.0f };
  Ray2D r4 = Ray2D(p1, p2);
  EXPECT_EQ(r4.initial().x(), 0.0f);
  EXPECT_EQ(r4.initial().y(), -1.0f);
  EXPECT_EQ(r4.direction().x(), 0.0f);
  EXPECT_EQ(r4.direction().y(), 0.0f);

  // Конструктор копирования
  Ray2D r5 = r4;
  EXPECT_EQ(r4, r5);
}

TEST(ray2d_test, test_initializer_list)
{
  // Тестирование конструкторов со списком иициализации

  Point2D p1 = { 0.0f, 3.0f };
  Point2D p2 = { 0.0f, -1.0f };
  Point2D p3 = { 6.0f, 7.0f };

  // В списке одна точка
  Ray2D r1 = { p1 };
  EXPECT_EQ(r1.initial().x(), 0.0f);
  EXPECT_EQ(r1.initial().y(), 0.0f);
  EXPECT_EQ(r1.direction().x(), 0.0f);
  EXPECT_EQ(r1.direction().y(), 1.0f);

  // В списке три точки
  Ray2D r2 = { p1, p2, p3};
  EXPECT_EQ(r2.initial().x(), 0.0f);
  EXPECT_EQ(r2.initial().y(), -1.0f);
  EXPECT_EQ(r2.direction().x(), 0.0f);
  EXPECT_EQ(r2.direction().y(), 0.0f);

  // В списке два числа
  Ray2D r3 = { 0.0f, 2.0f};
  EXPECT_EQ(r3.initial().x(), 0.0f);
  EXPECT_EQ(r3.initial().y(), 0.0f);
  EXPECT_EQ(r3.direction().x(), 0.0f);
  EXPECT_EQ(r3.direction().y(), 1.0f);

  // В списке шесть чисел
  Ray2D r4 = { 0.0f, 3.0f, 0.0f, -1.0f, 4.0f, 5.0f};
  EXPECT_EQ(r2.initial().x(), 0.0f);
  EXPECT_EQ(r2.initial().y(), -1.0f);
  EXPECT_EQ(r2.direction().x(), 0.0f);
  EXPECT_EQ(r2.direction().y(), 0.0f);
}

TEST(ray2d_test, test_assignment)
{
  Point2D p1 = { 0.0f, 3.0f };
  Point2D p2 = { 0.0f, -1.0f };
  Ray2D r1 = { p1, p2 };
  EXPECT_EQ(r1.initial().x(), 0.0f);
  EXPECT_EQ(r1.initial().y(), -1.0f);
  EXPECT_EQ(r1.direction().x(), 0.0f);
  EXPECT_EQ(r1.direction().y(), 0.0f);
}

TEST(ray2d_test, test_equality)
{
  Ray2D r1 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
  Ray2D r2 = { { 1.0f, 2.0f }, { 3.0f, 4.0f } };
  Ray2D r3 = { { 1.1f, 2.0f }, { 3.0f, 4.0f } };

  EXPECT_EQ(r1, r2);
  EXPECT_NE(r1, r3);
}

// Тестирование на перемещение
TEST(ray2d_test, test_move)
{
  Ray2D r1 = { 1.0f, 2.0f, 3.0f, 4.0f };
  Ray2D r2 = { 1.1f, 2.2f, 3.3f, 4.4f };

  // Оператор перемещения
  r1 = std::move(r2);
  EXPECT_EQ(r1, Ray2D(1.1f, 2.2f, 3.3f, 4.4f));
  EXPECT_EQ(r2, Ray2D(1.0f, 2.0f, 3.0f, 4.0f));

  // Конструктор перемещеиня
  Ray2D r3 = std::move(r1);
  EXPECT_EQ(r3, Ray2D(1.1f, 2.2f, 3.3f, 4.4f));
  EXPECT_EQ(r1, Ray2D(1.0f, 0.0f, 0.0f, 0.0f));
}

TEST(ray2d_test, test_calculus)
{
  // Тестирование инверсии луча
  Ray2D r1 = { { 4.0f, 0.0f }, { 1.0f, 0.0f } };
  EXPECT_EQ(-r1 , Ray2D(0.0f, 0.0f, 1.0f, 0.0f));

  // Тестирование изменения начальной точки
  Point2D p1 = { 0.0f, 0.0f };
  r1.SetInitial(p1);
  EXPECT_EQ(r1 , Ray2D(1.0f, 0.0f, 0.0f, 0.0f));

  // Тестирование изменения направления луча
  Point2D p2 = { 0.0f, 6.0f };
  r1.SetDirection(p2);
  EXPECT_EQ(r1 , Ray2D(0.0f, 1.0f, 0.0f, 0.0f));

  // Тестирование сдвига луча в горизонтальном направлении
  r1.HorizontalMove(-1.0f);
  EXPECT_EQ(r1 , Ray2D(-1.0f, 1.0f, -1.0f, 0.0f));

  // Тестирование сдвига луча в вертикальном направлении
  r1.VerticalMove(-1.0f);
  EXPECT_EQ(r1 , Ray2D(-1.0f, 0.0f, -1.0f, -1.0f));

  // Тестирование вращения направления луча
  r1 = {1.0f, 0.0f, 0.0f, 0.0f};
  r1.RotateDirection(90);
  EXPECT_EQ(r1 , Ray2D(0.0f, 1.0f, 0.0f, 0.0f));
}

TEST(ray2d_test, test_intersection)
{   
  Box2D b1 = { { 2.0f, 2.0f }, { 4.0f, 4.0f } };
  Box2D b2 = { { -3.0f, -3.0f }, { -1.0f, -1.0f } };
  Box2D b3 = { { -1.0f, -1.0f }, { 1.0f, 1.8f } };

  Ray2D r1 = { { 1.0f, 1.0f }, { 0.0f, 0.0f } };
  Ray2D r2 = { { 0.0f, 0.0f }, { 1.0f, 1.0f } };
  Ray2D r3 = { { 0.0f, 0.0f }, { 3.0f, -2.0f } };

  EXPECT_EQ(r1.Intersection(b1), true);
  EXPECT_EQ(r1.Intersection(b2), false);
  EXPECT_EQ(r1.Intersection(b3), true);

  EXPECT_EQ(r2.Intersection(b1), true);
  EXPECT_EQ(r2.Intersection(b2), false);
  EXPECT_EQ(r2.Intersection(b3), true);

  EXPECT_EQ(r3.Intersection(b1), false);
  EXPECT_EQ(r3.Intersection(b2), false);
  EXPECT_EQ(r3.Intersection(b3), false);
}

TEST(ray2d_test, test_output)
{
  std::stringstream s;
  s << Ray2D( { 0.0f, 1.0f }, { 0.0f, 0.0f } );
  EXPECT_EQ(s.str(), "Ray2D {initial point: {0, 0}, direction: {0, 1}}");
}
