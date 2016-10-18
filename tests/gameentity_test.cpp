#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"

TEST(gameentity_test, test_space)
{
  Space s1;
  EXPECT_EQ(s1.GetField().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s1.GetField().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s1.GetField().rightTopPoint().x(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetField().rightTopPoint().y(), SPACE_WIDTH);
  EXPECT_EQ(s1.GetHeight(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetWidth(), SPACE_WIDTH);

  Space s2 = Space(300.0f, 400.0f);
  EXPECT_EQ(s2.GetField().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s2.GetField().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s2.GetField().rightTopPoint().x(), 300);
  EXPECT_EQ(s2.GetField().rightTopPoint().y(), 400);
  EXPECT_EQ(s2.GetHeight(), 400);
  EXPECT_EQ(s2.GetWidth(), 300);
}

TEST(gameentity_test, test_obstacle)
{
  Point2D p1 = { 100.0f, 200.0f };
  Obstacle o1 = Obstacle(p1);
  EXPECT_EQ(o1.GetBody().leftBottomPoint().x(), 100.0f - OBSTACLE_WIDTH / 2);
  EXPECT_EQ(o1.GetBody().leftBottomPoint().x(), 100.0f - OBSTACLE_HEIGHT / 2);
  EXPECT_EQ(o1.GetBody().rightTopPoint().x(), 100.0f + OBSTACLE_WIDTH / 2);
  EXPECT_EQ(o1.GetBody().rightTopPoint().x(), 100.0f + OBSTACLE_HEIGHT / 2);

  EXPECT_EQ(o1.GetHeight(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.GetWidth(), OBSTACLE_WIDTH);

  EXPECT_EQ(o1.GetHP(), OBSTACLE_HIT_POINTS);
  EXPECT_EQ(o1.IsAlive(), true);

  EXPECT_EQ(o1.GetCoordinate(), p1);
}


TEST(gameentity_test, test_bullet)
{
  Ray2D r1 = { 0.0f, 1.0f, 50.0f, 50.0f };
  Point2D p1 = { 100.0f, 100.0f };
  Bullet b1 = Bullet(r1, p1);

  EXPECT_EQ(b1.GetBody().leftBottomPoint().x(), 100.0f - BULLET_WIDTH / 2);
  EXPECT_EQ(b1.GetBody().leftBottomPoint().x(), 100.0f - BULLET_HEIGHT / 2);
  EXPECT_EQ(b1.GetBody().rightTopPoint().x(), 100.0f + BULLET_WIDTH / 2);
  EXPECT_EQ(b1.GetBody().rightTopPoint().x(), 100.0f + BULLET_HEIGHT / 2);

  EXPECT_EQ(b1.GetDirection(), r1);
  EXPECT_EQ(b1.GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b1.GetDamage(), BULLET_DAMAGE);

  EXPECT_EQ(b1.GetHeight(), BULLET_HEIGHT);
  EXPECT_EQ(b1.GetWidth(), BULLET_WIDTH);

  EXPECT_EQ(b1.GetHP(), BULLET_HIT_POINTS);
  EXPECT_EQ(b1.IsAlive(), true);

  EXPECT_EQ(b1.GetCoordinate(), p1);
}

TEST(gameentity_test, test_gun)
{
  Point2D p1 = { 100.0f, 100.0f };
  Gun g1 = Gun(p1);

  EXPECT_EQ(g1.GetBody().leftBottomPoint().x(), 100.0f - GUN_WIDTH / 2);
  EXPECT_EQ(g1.GetBody().leftBottomPoint().x(), 100.0f - GUN_HEIGHT / 2);
  EXPECT_EQ(g1.GetBody().rightTopPoint().x(), 100.0f + GUN_WIDTH / 2);
  EXPECT_EQ(g1.GetBody().rightTopPoint().x(), 100.0f + GUN_HEIGHT / 2);

  EXPECT_EQ(g1.GetSpeed(), GUN_SPEED);


  EXPECT_EQ(g1.GetHeight(), GUN_HEIGHT);
  EXPECT_EQ(g1.GetWidth(), GUN_WIDTH);

  EXPECT_EQ(g1.GetHP(), GUN_HIT_POINTS);
  EXPECT_EQ(g1.IsAlive(), true);

  EXPECT_EQ(g1.GetCoordinate(), p1);
  EXPECT_EQ(g1.GetVelocity(), GUN_VELOCITY);

  EXPECT_EQ(g1.GetNumberOfLives(), START_NUMBER_OF_LIFES);
  for (int i = START_NUMBER_OF_LIFES; i > 0; i--) g1.DecreaseOneLife();
  EXPECT_EQ(g1.IsGameOver(), true);
}

TEST(gameentity_test, test_alien)
{
  Point2D p1 = { 100.0f, 100.0f };
  Alien a1 = Alien(p1);

  EXPECT_EQ(a1.GetBody().leftBottomPoint().x(), 100.0f - ALIEN_WIDTH / 2);
  EXPECT_EQ(a1.GetBody().leftBottomPoint().x(), 100.0f - ALIEN_HEIGHT / 2);
  EXPECT_EQ(a1.GetBody().rightTopPoint().x(), 100.0f + ALIEN_WIDTH / 2);
  EXPECT_EQ(a1.GetBody().rightTopPoint().x(), 100.0f + ALIEN_HEIGHT / 2);

  EXPECT_EQ(a1.GetSpeed(), START_ALIEN_SPEED);

  EXPECT_EQ(a1.GetHeight(), ALIEN_HEIGHT);
  EXPECT_EQ(a1.GetWidth(), ALIEN_WIDTH);

  EXPECT_EQ(a1.GetHP(), ALIEN_HIT_POINTS);
  EXPECT_EQ(a1.IsAlive(), true);

  EXPECT_EQ(a1.GetCoordinate(), p1);
  EXPECT_EQ(a1.GetVelocity(), ALIEN_VELOCITY);

  EXPECT_EQ(a1.GetXshift(), ALIEN_XSHIFT);
  EXPECT_EQ(a1.GetYshift(), ALIEN_YSHIFT);
}
