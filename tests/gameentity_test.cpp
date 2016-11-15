#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include <string>

using namespace std;

TEST(gameentity_test, test_space_construction)
{
  Space s1;
  EXPECT_EQ(s1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s1.GetBody().rightTopPoint().x(), SPACE_WIDTH);
  EXPECT_EQ(s1.GetBody().rightTopPoint().y(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetHeight(), SPACE_HEIGHT);
  EXPECT_EQ(s1.GetWidth(), SPACE_WIDTH);
  EXPECT_EQ(s1.IsCreated(), true);

  Space s2 = Space(Point2D(250.0f, 250.0f));
  EXPECT_EQ(s2.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s2.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s2.GetBody().rightTopPoint().x(), 500.0f);
  EXPECT_EQ(s2.GetBody().rightTopPoint().y(), 500.0f);
  EXPECT_EQ(s2.GetBody().Height(), SPACE_HEIGHT);
  EXPECT_EQ(s2.GetBody().Width(), SPACE_WIDTH);
  EXPECT_EQ(s2.IsCreated(), true);

  Space s3 = Space(Box2D(0.0f, 0.0f, 400.0f, 400.0f));
  EXPECT_EQ(s3.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s3.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s3.GetBody().rightTopPoint().x(), 400.0f);
  EXPECT_EQ(s3.GetBody().rightTopPoint().y(), 400.0f);
  EXPECT_EQ(s3.GetBody().Height(), 400.0f);
  EXPECT_EQ(s3.GetBody().Width(), 400.0f);
  EXPECT_EQ(s3.IsCreated(), true);
}

TEST(gameentity_test, test_obstacle_construction)
{
  Obstacle o1;
  EXPECT_EQ(o1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o1.GetBody().rightTopPoint().x(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1.GetBody().rightTopPoint().y(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1.GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1.IsAlive(), true);
  EXPECT_EQ(o1.IsCreated(), true);


  Point2D p1 = { 100.0f, 105.0f };
  Obstacle o2 = Obstacle(p1);
  EXPECT_EQ(o2.GetBody().leftBottomPoint().x(), 100.0f - OBSTACLE_WIDTH / 2.0f);
  EXPECT_EQ(o2.GetBody().leftBottomPoint().y(), 105.0f - OBSTACLE_HEIGHT / 2.0f);
  EXPECT_EQ(o2.GetBody().rightTopPoint().x(), 100.0f + OBSTACLE_WIDTH / 2.0f);
  EXPECT_EQ(o2.GetBody().rightTopPoint().y(), 105.0f + OBSTACLE_HEIGHT / 2.0f);
  EXPECT_EQ(o2.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o2.GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o2.IsAlive(), true);
  EXPECT_EQ(o2.IsCreated(), true);

  Box2D b1 = {0.0f, 0.0f, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
  Obstacle o3 = Obstacle(b1);
  EXPECT_EQ(o3.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o3.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o3.GetBody().rightTopPoint().x(), OBSTACLE_WIDTH);
  EXPECT_EQ(o3.GetBody().rightTopPoint().y(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3.GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3.GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o3.IsAlive(), true);
  EXPECT_EQ(o3.IsCreated(), true);
}

TEST(gameentity_test, test_bullet_construction)
{
  Gun g;

  Bullet b0 = Bullet();
  EXPECT_EQ(b0.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b0.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b0.GetBody().rightTopPoint().x(), BULLET_WIDTH);
  EXPECT_EQ(b0.GetBody().rightTopPoint().y(), BULLET_HEIGHT);
  EXPECT_EQ(b0.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b0.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b0.GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b0.GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b0.GetTrajectory().direction(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + 1.0f));
  EXPECT_EQ(b0.GetTrajectory().initial(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f));
  //EXPECT_EQ(b1.GetTrajectory(), Ray2D(Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + BULLET_SPEED), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f)));
  EXPECT_EQ(b0.IsAlive(), true);
  EXPECT_EQ(b0.IsCreated(), true);
  EXPECT_EQ(b0.GetShooter(), nullptr);

  Bullet b1 = Bullet(g);
  EXPECT_EQ(b1.GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b1.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b1.GetBody().rightTopPoint().x(), BULLET_WIDTH);
  EXPECT_EQ(b1.GetBody().rightTopPoint().y(), BULLET_HEIGHT);
  EXPECT_EQ(b1.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b1.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b1.GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b1.GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b1.GetTrajectory().direction(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + 1.0f));
  EXPECT_EQ(b1.GetTrajectory().initial(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f));
  //EXPECT_EQ(b1.GetTrajectory(), Ray2D(Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + BULLET_SPEED), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f)));
  EXPECT_EQ(b1.IsAlive(), true);
  EXPECT_EQ(b1.IsCreated(), true);
  EXPECT_EQ(b1.GetShooter(), &g);

  Point2D p1 = { 0.0f, 1.0f };
  Point2D p2 = { 0.0f, 3.0f };
  Bullet b2 = Bullet(Ray2D(p2, p1), g);
  EXPECT_EQ(b2.GetBody().leftBottomPoint().x(), p1.x() - BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b2.GetBody().leftBottomPoint().y(), p1.y() - BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b2.GetBody().rightTopPoint().x(), p1.x() + BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b2.GetBody().rightTopPoint().y(), p1.y() + BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b2.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b2.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b2.GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b2.GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b2.GetTrajectory().direction(), p2 - Point2D(0.0f, 1.0f));
  EXPECT_EQ(b2.GetTrajectory().initial(), p1);
  EXPECT_EQ(b2.IsAlive(), true);
  EXPECT_EQ(b2.IsCreated(), true);
  EXPECT_EQ(b2.GetShooter(), &g);

  Bullet b6 = Bullet(Ray2D(p2, p1), 2.0f, 1.0f, g);
  EXPECT_EQ(b6.GetBody().leftBottomPoint().x(), p1.x() - BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b6.GetBody().leftBottomPoint().y(), p1.y() - BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b6.GetBody().rightTopPoint().x(), p1.x() + BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b6.GetBody().rightTopPoint().y(), p1.y() + BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b6.GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b6.GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b6.GetSpeed(), 2.0f);
  EXPECT_EQ(b6.GetDamage(), 1.0f);
  EXPECT_EQ(b6.GetTrajectory().direction(), p2 - Point2D(0.0f, 1.0f));
  EXPECT_EQ(b6.GetTrajectory().initial(), p1);
  EXPECT_EQ(b6.IsAlive(), true);
  EXPECT_EQ(b6.IsCreated(), true);
  EXPECT_EQ(b6.GetShooter(), &g);
}

TEST(gameentity_test, test_gun_construction)
{
  Gun g1;
  EXPECT_EQ(g1.GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g1.GetBody().leftBottomPoint().y(), -GUN_HEIGHT / 2.0f);
  EXPECT_EQ(g1.GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g1.GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g1.GetFiringRate(), GUN_FIRING_RATE);
  EXPECT_EQ(g1.IsAlive(), true);
  EXPECT_EQ(g1.IsCreated(), true);

  Gun g2 = Gun(Point2D(SPACE_WIDTH / 2, GUN_HEIGHT / 2.0f));
  EXPECT_EQ(g2.GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g2.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g2.GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g2.GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g2.GetFiringRate(), GUN_FIRING_RATE);
  EXPECT_EQ(g2.IsAlive(), true);
  EXPECT_EQ(g2.IsCreated(), true);

  Gun g3 = Gun(Point2D(SPACE_WIDTH / 2, GUN_HEIGHT / 2.0f), 100, 1.0f);
  EXPECT_EQ(g3.GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g3.GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g3.GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g3.GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g3.GetAmmo(), 100);
  EXPECT_EQ(g3.GetFiringRate(), 1.0f);
  EXPECT_EQ(g3.IsAlive(), true);
  EXPECT_EQ(g3.IsCreated(), true);
}

TEST(gameentity_test, test_alien_construction)
{
  Alien a1;
  EXPECT_EQ(a1.GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a1.GetBody().leftBottomPoint().y(), SPACE_HEIGHT / 2.0f - ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a1.GetBody().rightTopPoint().x(), SPACE_WIDTH / 2.0f + ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a1.GetBody().rightTopPoint().y(), SPACE_HEIGHT / 2.0f + ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a1.GetBody().Height(), ALIEN_HEIGHT);
  EXPECT_EQ(a1.GetBody().Width(), ALIEN_WIDTH);
  EXPECT_EQ(a1.GetFiringRate(), ALIEN_FIRING_RATE);
  EXPECT_EQ(a1.IsAlive(), true);
  EXPECT_EQ(a1.IsCreated(), true);

  Point2D p2 = { 10.0f, 11.0f };
  Alien a2 = Alien(p2);
  EXPECT_EQ(a2.GetBody().leftBottomPoint().x(), p2.x() - ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a2.GetBody().leftBottomPoint().y(), p2.y() - ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a2.GetBody().rightTopPoint().x(), p2.x() + ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a2.GetBody().rightTopPoint().y(), p2.y() + ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a2.GetBody().Height(), ALIEN_HEIGHT);
  EXPECT_EQ(a2.GetBody().Width(), ALIEN_WIDTH);
  EXPECT_EQ(a2.IsAlive(), true);
  EXPECT_EQ(a2.IsCreated(), true);

  Point2D p1 = {0.0f, 0.0f};
  Alien a3 = Alien(Box2D(p1, p2));
  EXPECT_EQ(a3.GetBody().leftBottomPoint().x(), p1.x());
  EXPECT_EQ(a3.GetBody().leftBottomPoint().y(), p1.y());
  EXPECT_EQ(a3.GetBody().rightTopPoint().x(), p2.x());
  EXPECT_EQ(a3.GetBody().rightTopPoint().y(), p2.y());
  EXPECT_EQ(a3.GetBody().Height(), p2.y() - p1.y());
  EXPECT_EQ(a3.GetBody().Width(), p2.x() - p1.x());
  EXPECT_EQ(a3.IsAlive(), true);
  EXPECT_EQ(a3.IsCreated(), true);
}

TEST(gameentity_test, test_exceptions)
{
  Bullet b;
  EXPECT_THROW(b.SetDamage(-100), std::invalid_argument);
  EXPECT_THROW(b.SetHP(200),std::invalid_argument);
  EXPECT_THROW(b.SetCoordinate(Point2D(-10.0f, -10.f)), std::invalid_argument);
  EXPECT_THROW(b.SetCoordinate(Point2D(1000.0f, 1000.f)), std::invalid_argument);

  Gun g;
  EXPECT_THROW(g.Move(1000.0f), std::invalid_argument);
  EXPECT_THROW(g.SetFiringRate(-100.0f), std::invalid_argument);
  EXPECT_THROW(g.SetFiringRate(0.0f), std::invalid_argument);
  EXPECT_THROW(g.SetHP(200),std::invalid_argument);
  EXPECT_THROW(g.SetCoordinate(Point2D(-10.0f, -10.f)), std::invalid_argument);
  EXPECT_THROW(g.SetCoordinate(Point2D(1000.0f, 1000.f)), std::invalid_argument);

  Alien a;
  EXPECT_THROW(a.SetFiringRate(-100.0f), std::invalid_argument);
  EXPECT_THROW(a.SetFiringRate(0.0f), std::invalid_argument);
  EXPECT_THROW(a.SetHP(200),std::invalid_argument);
  EXPECT_THROW(a.SetCoordinate(Point2D(-10.0f, -10.f)), std::invalid_argument);
  EXPECT_THROW(a.SetCoordinate(Point2D(1000.0f, 1000.f)), std::invalid_argument);
}

TEST(gameentity_test, test_output)
{
  stringstream str;

  string line = "--------------\n";
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
  a.PrintInfo(str);
  EXPECT_EQ(str.str(), line + name_alien + alive + center_1 + width_1 + height_1 + xs + ys + rate + line);

  Bullet b;
  str.str(string());
  b.PrintInfo(str);
  EXPECT_EQ(str.str(), line + name_bullet + alive + traj + speed + damage + width_2 + height_2 + line);

  Gun g;
  str.str(string());
  g.PrintInfo(str);
  EXPECT_EQ(str.str(), line + name_gun + alive + center_3 + width_1 + height_1 + ammo + rate + line);

  Obstacle o;
  str.str(string());
  o.PrintInfo(str);
  EXPECT_EQ(str.str(), line + name_obstacle + alive + health + center_2 + width_2 + height_2 + line);

  Space s;
  str.str(string());
  s.PrintInfo(str);
  EXPECT_EQ(str.str(), line + name_space + created + center_1 + width_3 + height_3 + line);
}
