#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "gun.hpp"
#include "ray2d.hpp"
#include "alien.hpp"
#include <sstream>
#include <unordered_set>

TEST(gameentity_test, test_space_construction)
{
  Space s1;
  EXPECT_EQ(s1.body().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s1.body().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s1.body().rightTopPoint().x(), SPACE_HEIGHT);
  EXPECT_EQ(s1.body().rightTopPoint().y(), SPACE_WIDTH);
  EXPECT_EQ(s1.body().Height(), SPACE_HEIGHT);
  EXPECT_EQ(s1.body().Width(), SPACE_WIDTH);

  Space s2 = Space(300.0f,400.0f);
  EXPECT_EQ(s2.body().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s2.body().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s2.body().rightTopPoint().x(), 300);
  EXPECT_EQ(s2.body().rightTopPoint().y(), 400);
  EXPECT_EQ(s2.body().Height(), 400);
  EXPECT_EQ(s2.body().Width(), 300);
}

TEST(gameentity_test, test_obstacle_construction)
{
  Obstacle o1;
  EXPECT_EQ(o1.body().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o1.body().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o1.body().rightTopPoint().x(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.body().rightTopPoint().y(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1.body().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.body().Width(), OBSTACLE_WIDTH);


  Point2D p1 = {100.0f,105.0f};
  Obstacle o2 = Obstacle(p1);
  EXPECT_EQ(o2.body().leftBottomPoint().x(), 100.0f);
  EXPECT_EQ(o2.body().leftBottomPoint().y(), 105.0f);
  EXPECT_EQ(o2.body().rightTopPoint().x(), 100.0f + OBSTACLE_HEIGHT);
  EXPECT_EQ(o2.body().rightTopPoint().y(), 105.0f + OBSTACLE_WIDTH);
  EXPECT_EQ(o2.body().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o2.body().Width(), OBSTACLE_WIDTH);
}
/*
TEST(gameentity_test, test_gun_construction)
{
  Gun g1;
  EXPECT_EQ(g1.body().leftBottomPoint().x(), SPACE_WIDTH / 2 - GUN_WIDTH / 2);
  EXPECT_EQ(g1.body().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g1.body().rightTopPoint().x(), GUN_HEIGHT);
  EXPECT_EQ(g1.body().rightTopPoint().y(), GUN_WIDTH);
  EXPECT_EQ(g1.body().Height(), GUN_HEIGHT);
  EXPECT_EQ(g1.body().Width(), GUN_WIDTH);
}
*/
