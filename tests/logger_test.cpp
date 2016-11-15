#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include "logger.hpp"
#include <string>
#include <vector>

using namespace std;

TEST(logger_test, test_log)
{
  stringstream str;

  string action1 = "Created\n";
  string action2 = "Destroyed\n";
  string action3 = "Shoots\n";
  string action4 = "Caused damage\n";
  string action5 = "Suffered damage\n";
  string name_alien = "Alien ";
  string name_bullet = "Bullet ";
  string name_gun = "Gun ";
  string name_obstacle = "Obstacle ";
  string name_space = "Space ";
  string center_1 = "(Point2D {250, 250}) ";
  string center_2 = "(Point2D {2.5, 2.5}) ";
  string center_3 = "(Point2D {250, 0}) ";

  Alien a;
  Bullet b;
  Gun g;
  Obstacle o;
  Space sp;

  Box2D box;
  Point2D point;
  Ray2D ray;

  int i = 10;

  vector<Gun> v(3);

  Logger::Instance().Log(a, ActionType::Creation, str);
  EXPECT_EQ(str.str(), name_alien + center_1 + action1);

  str.str(string());
  Logger::Instance().Log(g, ActionType::Shot, str);
  EXPECT_EQ(str.str(), name_gun + center_3 + action3);

  str.str(string());
  Logger::Instance().Log(o, ActionType::SufferDamage, str);
  EXPECT_EQ(str.str(), name_obstacle + center_2 + action5);

  str.str(string());
  Logger::Instance().Log(sp, ActionType::Destroying, str);
  EXPECT_EQ(str.str(), name_space + center_1 + action2);

  str.str(string());
  Logger::Instance().Log(box, str);
  EXPECT_EQ(str.str(), "Box2D {Point2D {0, 0}, Point2D {0, 0}}");

  str.str(string());
  Logger::Instance().Log(point, str);
  EXPECT_EQ(str.str(), "Point2D {0, 0}");

  str.str(string());
  Logger::Instance().Log(ray, str);
  EXPECT_EQ(str.str(), "Ray2D {initial point: {0, 0}, direction: {1, 0}}");

  str.str(string());
  Logger::Instance().Log(i, str);
  EXPECT_EQ(str.str(), "10");

  str.str(string());
  Logger::Instance().Log(v, ActionType::Creation, str);
  EXPECT_EQ(str.str(), name_gun + center_3 + " " +
                       name_gun + center_3 + " " +
                       name_gun + center_3 + " " + action1);
}
