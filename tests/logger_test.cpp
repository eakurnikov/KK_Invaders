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
  string str = "";

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

  /*fstream f("D:/C++ Projects/private-void.KK_Invaders/KK_Invaders/Log.txt", std::ios::out);
  f.close();
  Logger::Instance().Log(a, ActionType::Creation);
  f.open("D:/C++ Projects/private-void.KK_Invaders/KK_Invaders/Log.txt", std::ios::in | std::ios::out);
  f >> str;
  EXPECT_EQ(str, name_alien + center_1 + action1);
  str = "";
  f.close();

  /*Logger::Instance().Log(g, ActionType::Shot);
  f >> str;
  EXPECT_EQ(str, name_gun + center_3 + action3);
  f.flush();

  Logger::Instance().Log(o, ActionType::SufferDamage);
  f >> str;
  EXPECT_EQ(str, name_obstacle + center_2 + action5);
  f.flush();

  Logger::Instance().Log(sp, ActionType::Destroying);
  f >> str;
  EXPECT_EQ(str, name_space + center_1 + action2);
  f.flush();

  Logger::Instance().Log(box);
  f >> str;
  EXPECT_EQ(str, "Box2D {Point2D {0, 0}, Point2D {0, 0}}");
  f.flush();

  Logger::Instance().Log(point);
  f >> str;
  EXPECT_EQ(str, "Point2D {0, 0}");
  f.flush();

  Logger::Instance().Log(ray);
  f >> str;
  EXPECT_EQ(str, "Ray2D {initial point: {0, 0}, direction: {1, 0}}");
  f.flush();

  Logger::Instance().Log(i);
  f >> str;
  EXPECT_EQ(str, "10");
  f.flush();

  Logger::Instance().Log(v, ActionType::Creation);
  f >> str;
  EXPECT_EQ(str, name_gun + center_3 + " " + name_gun + center_3 + " " + name_gun + center_3 + " " + action1);
  f.flush();*/

  //f.close();
}
