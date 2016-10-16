#include "gtest/gtest.h"
#include "box2d.hpp"
#include <sstream>
#include <unordered_set>

TEST(box2d_test, test_construction)
{
  // Тест на создание объекта по умолчанию.
  Box2D b1;
  EXPECT_EQ(b1.leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b1.leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b1.rightTopPoint().x(), 0.0f);
  EXPECT_EQ(b1.rightTopPoint().y(), 0.0f);

  // Тесты на создание объекта с различными параметрами

  // Две координаты
  Box2D b2 = Box2D(1.0f, 3.0f);
  EXPECT_EQ(b2.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b2.leftBottomPoint().y(), 3.0f);
  EXPECT_EQ(b2.rightTopPoint().x(), 2.0f);
  EXPECT_EQ(b2.rightTopPoint().y(), 4.0f);

  // Четыре координаты
  Box2D b3 = Box2D(1.1f, 1.2f, 2.4f, 2.5f);
  EXPECT_EQ(b3.leftBottomPoint().x(), 1.1f);
  EXPECT_EQ(b3.leftBottomPoint().y(), 1.2f);
  EXPECT_EQ(b3.rightTopPoint().x(), 2.4f);
  EXPECT_EQ(b3.rightTopPoint().y(), 2.5f);

  // Одна точка
  Point2D p1 = { 1.0f, 3.0f };
  Box2D b4 = Box2D(p1);
  EXPECT_EQ(b4.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b4.leftBottomPoint().y(), 3.0f);
  EXPECT_EQ(b4.rightTopPoint().x(), 2.0f);
  EXPECT_EQ(b4.rightTopPoint().y(), 4.0f);

  // Две точки
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b5 = Box2D(p1, p2);
  EXPECT_EQ(b5.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b5.leftBottomPoint().y(), 3.0f);
  EXPECT_EQ(b5.rightTopPoint().x(), 3.0f);
  EXPECT_EQ(b5.rightTopPoint().y(), 4.0f);

  // Тест на создание копии объекта
  Box2D b6 = b5;
  EXPECT_EQ(b5, b6);

  // Тест на CheckPoints
  Box2D b7 = Box2D(1.1f, 1.2f, -2.4f, -2.5f);
  EXPECT_EQ(b7.leftBottomPoint().x(), -2.4f);
  EXPECT_EQ(b7.leftBottomPoint().y(), -2.5f);
  EXPECT_EQ(b7.rightTopPoint().x(), 1.1f);
  EXPECT_EQ(b7.rightTopPoint().y(), 1.2f);

  // Конструктор с параметрами - точкой и двумя сторонами прямоугольника
  Box2D b8 = {1.1f, 1.2f, 2.0f, 2.0f};
  EXPECT_EQ(b8.leftBottomPoint().x(), 1.1f);
  EXPECT_EQ(b8.leftBottomPoint().y(), 1.2f);
  EXPECT_EQ(b8.rightTopPoint().x(), 2.0f);
  EXPECT_EQ(b8.rightTopPoint().y(), 2.0f);
}

TEST(box2d_test, test_initializer_list)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Point2D p3 = { 5.0f, 6.0f };
  Box2D b1 = { p1 };
  EXPECT_EQ(b1.leftBottomPoint().x(), 0.0);
  EXPECT_EQ(b1.leftBottomPoint().y(), 0.0);
  EXPECT_EQ(b1.rightTopPoint().x(), 1.0f);
  EXPECT_EQ(b1.rightTopPoint().y(), 2.0f);

  Box2D b2 = { p1, p2 };
  EXPECT_EQ(b2.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b2.leftBottomPoint().y(), 2.0f);
  EXPECT_EQ(b2.rightTopPoint().x(), 3.0f);
  EXPECT_EQ(b2.rightTopPoint().y(), 4.0f);

  Box2D b3 = { p1, p2, p3 };
  EXPECT_EQ(b3.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b3.leftBottomPoint().y(), 2.0f);
  EXPECT_EQ(b3.rightTopPoint().x(), 3.0f);
  EXPECT_EQ(b3.rightTopPoint().y(), 4.0f);

  Box2D b4 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };
  EXPECT_EQ(b4.leftBottomPoint().x(), 1.0f);
  EXPECT_EQ(b4.leftBottomPoint().y(), 2.0f);
  EXPECT_EQ(b4.rightTopPoint().x(), 3.0f);
  EXPECT_EQ(b4.rightTopPoint().y(), 4.0f);

  Box2D b5 = { 1.0f, 2.0f };
  EXPECT_EQ(b5.leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b5.leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b5.rightTopPoint().x(), 1.0f);
  EXPECT_EQ(b5.rightTopPoint().y(), 2.0f);
}


TEST(box2d_test, test_assignment)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b1;
  b1 = { p1, p2 };

  EXPECT_EQ(b1, Box2D(p1, p2));
}


TEST(box2d_test, test_equality)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 2.0f, 3.0f };
  Point2D p3 = { 2.0f, 3.0f };
  Point2D p4 = { 2.0f, 3.1f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p1, p3 };
  Box2D b3 = { p1, p4 };

  EXPECT_EQ(b1, b2);
  EXPECT_NE(b1, b3);
  EXPECT_LT(b1, b3);
}

// Тестирование на перемещение
TEST(box2d_test, test_move)
{
  Box2D b1 = { 1.0f, 2.0f, 3.0f, 4.0f };
  Box2D b2 = { 1.1f, 2.2f, 3.3f, 4.4f };

  // Оператор перемещения
  b1 = std::move(b2);
  EXPECT_EQ(b1, Box2D(1.1f, 2.2f, 3.3f, 4.4f));
  EXPECT_EQ(b2, Box2D(1.0f, 2.0f, 3.0f, 4.0f));

  // Конструктор перемещеиня
  Box2D b3 = std::move(b1);
  EXPECT_EQ(b3, Box2D(1.1f, 2.2f, 3.3f, 4.4f));
  EXPECT_EQ(b1, Box2D(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(box2d_test, test_set)
{
    // Тест на установку значения левой нижней точки.
    Point2D p1 = {1.0f, 1.0f};
    Box2D b1 = {0.0f, 0.0f, 1.0f, 1.0f};
    Box2D b2 = {1.0f, 1.0f, 2.0f, 2.0f};
    b1.SetLeftBottomPoint(p1);
    EXPECT_EQ(b1, b2);

    // Тест на установку значения центра.
    Box2D b3 = {0.0f, 0.0f, 2.0f, 2.0f};
    b3.SetCenter(Point2D(1.0f, 1.0f));
    EXPECT_EQ(b3.GetCenter(), p1);
}

TEST(box2d_test, test_height)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b1 = { p1, p2 };
  EXPECT_EQ(b1.Height(), 2.0f);
}

TEST(box2d_test, test_width)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b1 = { p1, p2 };
  EXPECT_EQ(b1.Width(), 2.0f);
}

TEST(box2d_test, test_perimeter)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b1 = { p1, p2 };
  EXPECT_EQ(b1.Perimeter(), 8.0f);
}

TEST(box2d_test, test_area)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Box2D b1 = { p1, p2 };
  EXPECT_EQ(b1.Area(), 4.0f);
}

TEST(box2d_test, test_getCenter)
{
  Point2D p1 = { 1.0f, 1.0f };
  Point2D p2 = { 3.0f, 3.0f };
  Box2D b1 = { p1, p2 };
  EXPECT_EQ(b1.GetCenter(), Point2D(2.0f, 2.0f));
}

TEST(box2d_test, test_intersection)
{
  Point2D p1 = { 2.0f, 3.0f };
  Point2D p2 = { 4.0f, 5.0f };
  Point2D p3 = { 1.0f, 1.0f };
  Point2D p4 = { 2.0f, 2.0f };
  Point2D p5 = { 3.0f, 1.0f };
  Point2D p6 = { 6.0f, 4.0f };
  Box2D b1 = { p1, p2 };
  Box2D b2 = { p3, p4 };
  Box2D b3 = { p5, p6 };
  EXPECT_NE(b1.IsBoxesIntersect(b2), true);
  EXPECT_EQ(b1.IsBoxesIntersect(b3), true);
}

TEST(box2d_test, test_calculus)
{
  Point2D p1 = { 1.0f, 2.0f };
  Box2D b1 = { 1.0f, 1.0f, 2.0f, 2.0f };
  float scale = 3.0f;
  EXPECT_EQ(-b1, Box2D(-1.0f, -1.0f, -2.0f, -2.0f));
  EXPECT_EQ(b1 - scale, Box2D(-2.0f, -2.0f, -1.0f, -1.0f));
  EXPECT_EQ(b1 + scale, Box2D(4.0f, 4.0f, 5.0f, 5.0f));
  EXPECT_EQ(b1 * scale, Box2D(3.0f, 3.0f, 6.0f, 6.0f));
  scale = 2.0f;
  EXPECT_EQ(b1 / scale, Box2D(0.5f, 0.5f, 1.0f, 1.0f));

  b1 += scale;
  EXPECT_EQ(b1, Box2D(3.0f, 3.0f, 4.0f, 4.0f));

  b1 -= scale;
  EXPECT_EQ(b1, Box2D(1.0f, 1.0f, 2.0f, 2.0f));

  b1 *= scale;
  EXPECT_EQ(b1, Box2D(1.0f, 1.0f, 4.0f, 4.0f));

  b1 /= scale;
  EXPECT_EQ(b1, Box2D(1.0f, 1.0f, 2.0f, 2.0f));

  Box2D b2 = { 1.0f, 1.0f, 4.0f, 4.0f };
  Box2D b3 = { 1.0f, 1.0f, 4.0f, 4.0f };
  EXPECT_LT(b1, b2);
  EXPECT_GT(b2, b1);
  EXPECT_LE(b2, b3);
  EXPECT_GE(b3, b2);

  b1+=p1;
  EXPECT_EQ(b1, Box2D(2.0f, 3.0f, 3.0f, 4.0f));

  b1 -= p1;
  EXPECT_EQ(b1, Box2D(1.0f, 1.0f, 2.0f, 2.0f));

  b1 *= p1;
  EXPECT_EQ(b1, Box2D(1.0f, 2.0f, 2.0f, 4.0f));

  b1 /= p1;
  EXPECT_EQ(b1, Box2D(1.0f, 1.0f, 2.0f, 2.0f));

  Box2D b4 = { 1.0f, 2.0f, 3.0f, 4.0f };
}

TEST(box2d_test, test_square_brackets)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  Point2D p3;
  Box2D b1 = { p1, p2 };

  EXPECT_EQ(b1[0], p1);
  EXPECT_EQ(b1[1], p2);
  EXPECT_EQ(b1[2], p3);
}

TEST(box2d_test, test_output)
{
  Point2D p1 = { 1.0f, 2.0f };
  Point2D p2 = { 3.0f, 4.0f };
  std::stringstream s;
  s << Box2D(p1, p2);
  EXPECT_EQ(s.str(), "Box2D {Point2D {1, 2}, Point2D {3, 4}}");
}
