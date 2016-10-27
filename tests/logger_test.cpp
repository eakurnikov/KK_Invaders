#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include "logger.hpp"
#include <string>

using namespace std;

TEST(logger_test, test_log)
{
  stringstream str;

  string s = "--------------\n";
  string action1 = "Created ";
  string action2 = "Destroyed ";
  string action3 = "Shoots ";
  string action4 = "Caused damage ";
  string action5 = "Suffered damage ";
  string name_alien = "Alien\n";
  string name_bullet = "Bullet\n";
  string name_gun = "Gun\n";
  string name_obstacle = "Obstacle\n";
  string name_space = "Space\n";
  string alive = " - Alive\n";
  string created = " - Created\n";
  string health = " - Health: 100\n";
  string center_1 = " - Center: Point2D {250, 250}\n";
  string center_2 = " - Center: Point2D {2.5, 2.5}\n";
  string center_3 = " - Center: Point2D {250, 0}\n";
  string width_1 = " - Width: 20\n";
  string height_1 = " - Height: 20\n";
  string width_2 = " - Width: 5\n";
  string height_2 = " - Height: 5\n";
  string width_3 = " - Width: 500\n";
  string height_3 = " - Height: 500\n";
  string traj = " - Trajectory: Ray2D {initial point: {2.5, 2.5}, direction: {2.5, 3.5}}\n";
  string speed = " - Speed: 10\n";
  string damage = " - Damage: 1\n";
  string ammo = " - Ammo: 100\n";
  string xs = " - X Shift: 1\n";
  string ys = " - Y Shift: 10\n";
  string rate = " - Firing rate: 1\n";

  Alien a;
  Bullet b;
  Gun g;
  Obstacle o;
  Space sp;

  Box2D box;
  Point2D point;
  Ray2D ray;

  int i = 10;

  Logger::Log(a, ActionType::CauseDamage, str);
  EXPECT_EQ(str.str(), s + action4 + name_alien + alive + center_1 + width_1 + height_1 + xs + ys + rate + s);

  str.str(string());
  Logger::Log(b, ActionType::Creation, str);
  EXPECT_EQ(str.str(), s + action1 + name_bullet + alive + traj + speed + damage + width_2 + height_2 + s);

  str.str(string());
  Logger::Log(g, ActionType::Shot, str);
  EXPECT_EQ(str.str(), s + action3 + name_gun + alive + center_3 + width_1 + height_1 + ammo + rate + s);

  str.str(string());
  Logger::Log(o, ActionType::SufferDamage, str);
  EXPECT_EQ(str.str(), s + action5 + name_obstacle + alive + health + center_2 + width_2 + height_2 + s);

  str.str(string());
  Logger::Log(sp, ActionType::Destroying, str);
  EXPECT_EQ(str.str(), s + action2 + name_space + created + center_1 + width_3 + height_3 + s);

  str.str(string());
  Logger::Log(box, str);
  EXPECT_EQ(str.str(), "Box2D {Point2D {0, 0}, Point2D {0, 0}}");

  str.str(string());
  Logger::Log(point, str);
  EXPECT_EQ(str.str(), "Point2D {0, 0}");

  str.str(string());
  Logger::Log(ray, str);
  EXPECT_EQ(str.str(), "Ray2D {initial point: {0, 0}, direction: {1, 0}}");

  str.str(string());
  Logger::Log(i, str);
  EXPECT_EQ(str.str(), "10");
}
