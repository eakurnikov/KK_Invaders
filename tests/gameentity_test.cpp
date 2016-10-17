#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"

TEST(gameentity_test, test_space_construction)
{
  Space s1;
  EXPECT_EQ(s1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s1.GetBody().rightTopPoint().x(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetBody().rightTopPoint().y(), SPACE_WIDTH);
  EXPECT_EQ(s1.GetBody().Height(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetBody().Width(), SPACE_WIDTH);

  Space s2 = Space(Point2D(250.0f, 250.0f));
  EXPECT_EQ(s2.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s2.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s2.GetBody().rightTopPoint().x(), 500);
  EXPECT_EQ(s2.GetBody().rightTopPoint().y(), 500);
  EXPECT_EQ(s2.GetBody().Height(), 500);
  EXPECT_EQ(s2.GetBody().Width(), 500);

  Space s3 = Space(Box2D(0.0f, 0.0f, 500.0f, 500.0f));
  EXPECT_EQ(s3.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s3.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s3.GetBody().rightTopPoint().x(), 500);
  EXPECT_EQ(s3.GetBody().rightTopPoint().y(), 500);
  EXPECT_EQ(s3.GetBody().Height(), 500);
  EXPECT_EQ(s3.GetBody().Width(), 500);
}

TEST(gameentity_test, test_obstacle_construction)
{
  Obstacle o1;
  EXPECT_EQ(o1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o1.GetBody().rightTopPoint().x(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.GetBody().rightTopPoint().y(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.GetBody().Width(), OBSTACLE_WIDTH);


  Point2D p1 = { 100.0f, 105.0f };
  Obstacle o2 = Obstacle(p1);
  EXPECT_EQ(o2.GetBody().leftBottomPoint().x(), 100.0f - OBSTACLE_WIDTH / 2);
  EXPECT_EQ(o2.GetBody().leftBottomPoint().y(), 105.0f - OBSTACLE_HEIGHT / 2);
  EXPECT_EQ(o2.GetBody().rightTopPoint().x(), 100.0f + OBSTACLE_HEIGHT / 2);
  EXPECT_EQ(o2.GetBody().rightTopPoint().y(), 105.0f + OBSTACLE_WIDTH / 2);
  EXPECT_EQ(o2.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o2.GetBody().Width(), OBSTACLE_WIDTH);

  Box2D b1 = {0.0f, 0.0f, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
  Obstacle o3 = Obstacle(b1);
  EXPECT_EQ(o3.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o3.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o3.GetBody().rightTopPoint().x(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3.GetBody().rightTopPoint().y(), OBSTACLE_WIDTH);
  EXPECT_EQ(o3.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3.GetBody().Width(), OBSTACLE_WIDTH);
}

TEST(gameentity_test, test_bullet_construction)
{
  Bullet b1;
  EXPECT_EQ(b1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b1.GetBody().rightTopPoint().x(), BULLET_HEIGHT);
  EXPECT_EQ(b1.GetBody().rightTopPoint().y(), BULLET_WIDTH);
  EXPECT_EQ(b1.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b1.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b1.GetTrajectory().direction(), Point2D(0.0f, 1.0f));
  EXPECT_EQ(b1.GetTrajectory().initial(), Point2D(0.0f, 0.0f));

  /*Point2D p1 = { 0.0f, 1.0f };
  Point2D p2 = { 2.0f, 4.0f };
  Point2D p3 = { 3.0f, 5.0f };
  Bullet b2 = Bullet(p1, p2, p3);
  EXPECT_EQ(b2.GetBody().leftBottomPoint(), p3);
  EXPECT_EQ(b2.GetBody().rightTopPoint().x(), 3.0f + BULLET_HEIGHT);
  EXPECT_EQ(b2.GetBody().rightTopPoint().y(), 5.0f + BULLET_WIDTH);
  EXPECT_EQ(b2.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b2.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b2.GetTrajectory().direction(), p1);
  EXPECT_EQ(b2.GetTrajectory().initial(), p2);*/
}


TEST(gameentity_test, test_gun_construction)
{
  Gun g1;
  EXPECT_EQ(g1.GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2 - GUN_WIDTH / 2);
  EXPECT_EQ(g1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g1.GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g1.GetBody().Width(), GUN_WIDTH);
}

/*TEST(gameentity_test, test_alien_construction)
{
  Point2D p1 = { 10.0f, 11.0f };
  Alien a1 = Alien(p1);
  EXPECT_EQ(a1.GetBody().leftBottomPoint(), p1);
  EXPECT_EQ(a1.GetBody().rightTopPoint().x(), 10.0f + ALIEN_HEIGHT);
  EXPECT_EQ(a1.GetBody().rightTopPoint().y(), 11.0f + ALIEN_WIDTH);
  EXPECT_EQ(a1.GetBody().Height(), ALIEN_HEIGHT);
  EXPECT_EQ(a1.GetBody().Width(), ALIEN_WIDTH);
}*/
