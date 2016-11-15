#include "gtest/gtest.h"
#include "space.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "gun.hpp"
#include "alien.hpp"
#include "factory.hpp"
#include <string>
#include <memory>

TEST(factory_test, test_factory_space_construction)
{
  std::unique_ptr<Space> s1 = Factory::Instance().Create<Space>();
  EXPECT_EQ(s1->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s1->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s1->GetBody().rightTopPoint().x(), SPACE_WIDTH);
  EXPECT_EQ(s1->GetBody().rightTopPoint().y(), SPACE_HEIGHT);
  EXPECT_EQ(s1->GetHeight(), SPACE_HEIGHT);
  EXPECT_EQ(s1->GetWidth(), SPACE_WIDTH);
  EXPECT_EQ(s1->IsCreated(), true);

  std::unique_ptr<Space> s2 = Factory::Instance().Create<Space>(Point2D(250.0f, 250.0f));
  EXPECT_EQ(s2->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s2->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s2->GetBody().rightTopPoint().x(), 500.0f);
  EXPECT_EQ(s2->GetBody().rightTopPoint().y(), 500.0f);
  EXPECT_EQ(s2->GetBody().Height(), SPACE_HEIGHT);
  EXPECT_EQ(s2->GetBody().Width(), SPACE_WIDTH);
  EXPECT_EQ(s2->IsCreated(), true);

  std::unique_ptr<Space> s3 = Factory::Instance().Create<Space>(Box2D(0.0f, 0.0f, 400.0f, 400.0f));
  EXPECT_EQ(s3->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(s3->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(s3->GetBody().rightTopPoint().x(), 400.0f);
  EXPECT_EQ(s3->GetBody().rightTopPoint().y(), 400.0f);
  EXPECT_EQ(s3->GetBody().Height(), 400.0f);
  EXPECT_EQ(s3->GetBody().Width(), 400.0f);
  EXPECT_EQ(s3->IsCreated(), true);
}

TEST(factory_test, test_factory_obstacle_construction)
{
  std::unique_ptr<Obstacle> o1 = Factory::Instance().Create<Obstacle>();
  EXPECT_EQ(o1->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o1->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o1->GetBody().rightTopPoint().x(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1->GetBody().rightTopPoint().y(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1->GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o1->GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o1->IsAlive(), true);
  EXPECT_EQ(o1->IsCreated(), true);


  Point2D p1 = { 100.0f, 105.0f };
  std::unique_ptr<Obstacle> o2 = Factory::Instance().Create<Obstacle>(p1);
  EXPECT_EQ(o2->GetBody().leftBottomPoint().x(), 100.0f - OBSTACLE_WIDTH / 2.0f);
  EXPECT_EQ(o2->GetBody().leftBottomPoint().y(), 105.0f - OBSTACLE_HEIGHT / 2.0f);
  EXPECT_EQ(o2->GetBody().rightTopPoint().x(), 100.0f + OBSTACLE_WIDTH / 2.0f);
  EXPECT_EQ(o2->GetBody().rightTopPoint().y(), 105.0f + OBSTACLE_HEIGHT / 2.0f);
  EXPECT_EQ(o2->GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o2->GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o2->IsAlive(), true);
  EXPECT_EQ(o2->IsCreated(), true);

  Box2D b1 = {0.0f, 0.0f, OBSTACLE_WIDTH, OBSTACLE_HEIGHT};
  std::unique_ptr<Obstacle> o3 = Factory::Instance().Create<Obstacle>(b1);
  EXPECT_EQ(o3->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(o3->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(o3->GetBody().rightTopPoint().x(), OBSTACLE_WIDTH);
  EXPECT_EQ(o3->GetBody().rightTopPoint().y(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3->GetBody().Height(), OBSTACLE_HEIGHT);
  EXPECT_EQ(o3->GetBody().Width(), OBSTACLE_WIDTH);
  EXPECT_EQ(o3->IsAlive(), true);
  EXPECT_EQ(o3->IsCreated(), true);
}

TEST(factory_test, test_factory_bullet_construction)
{
  Gun g;

  std::unique_ptr<Bullet> b0 = Factory::Instance().Create<Bullet>();
  EXPECT_EQ(b0->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b0->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b0->GetBody().rightTopPoint().x(), BULLET_WIDTH);
  EXPECT_EQ(b0->GetBody().rightTopPoint().y(), BULLET_HEIGHT);
  EXPECT_EQ(b0->GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b0->GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b0->GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b0->GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b0->GetTrajectory().direction(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + 1.0f));
  EXPECT_EQ(b0->GetTrajectory().initial(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f));
  //EXPECT_EQ(b1.GetTrajectory(), Ray2D(Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + BULLET_SPEED), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f)));
  EXPECT_EQ(b0->IsAlive(), true);
  EXPECT_EQ(b0->IsCreated(), true);
  EXPECT_EQ(b0->GetShooter(), nullptr);

  std::unique_ptr<Bullet> b1 = Factory::Instance().Create<Bullet>(g);
  EXPECT_EQ(b1->GetBody().leftBottomPoint().x(), 0.0f);
  EXPECT_EQ(b1->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(b1->GetBody().rightTopPoint().x(), BULLET_WIDTH);
  EXPECT_EQ(b1->GetBody().rightTopPoint().y(), BULLET_HEIGHT);
  EXPECT_EQ(b1->GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b1->GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b1->GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b1->GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b1->GetTrajectory().direction(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + 1.0f));
  EXPECT_EQ(b1->GetTrajectory().initial(), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f));
  //EXPECT_EQ(b1.GetTrajectory(), Ray2D(Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f + BULLET_SPEED), Point2D(BULLET_WIDTH / 2.0f, BULLET_HEIGHT / 2.0f)));
  EXPECT_EQ(b1->IsAlive(), true);
  EXPECT_EQ(b1->IsCreated(), true);
  EXPECT_EQ(b1->GetShooter(), &g);

  Point2D p1 = { 0.0f, 1.0f };
  Point2D p2 = { 0.0f, 3.0f };
  std::unique_ptr<Bullet> b2 = Factory::Instance().Create<Bullet>(Ray2D(p2, p1), g);
  EXPECT_EQ(b2->GetBody().leftBottomPoint().x(), p1.x() - BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b2->GetBody().leftBottomPoint().y(), p1.y() - BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b2->GetBody().rightTopPoint().x(), p1.x() + BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b2->GetBody().rightTopPoint().y(), p1.y() + BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b2->GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b2->GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b2->GetSpeed(), BULLET_SPEED);
  EXPECT_EQ(b2->GetDamage(), BULLET_DAMAGE);
  EXPECT_EQ(b2->GetTrajectory().direction(), p2 - Point2D(0.0f, 1.0f));
  EXPECT_EQ(b2->GetTrajectory().initial(), p1);
  EXPECT_EQ(b2->IsAlive(), true);
  EXPECT_EQ(b2->IsCreated(), true);
  EXPECT_EQ(b2->GetShooter(), &g);

  std::unique_ptr<Bullet> b3 = Factory::Instance().Create<Bullet>(Ray2D(p2, p1), 2.0f, 1.0f, g);
  EXPECT_EQ(b3->GetBody().leftBottomPoint().x(), p1.x() - BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b3->GetBody().leftBottomPoint().y(), p1.y() - BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b3->GetBody().rightTopPoint().x(), p1.x() + BULLET_WIDTH / 2.0f);
  EXPECT_EQ(b3->GetBody().rightTopPoint().y(), p1.y() + BULLET_HEIGHT / 2.0f);
  EXPECT_EQ(b3->GetBody().Height(), BULLET_HEIGHT);
  EXPECT_EQ(b3->GetBody().Width(), BULLET_WIDTH);
  EXPECT_EQ(b3->GetSpeed(), 2.0f);
  EXPECT_EQ(b3->GetDamage(), 1.0f);
  EXPECT_EQ(b3->GetTrajectory().direction(), p2 - Point2D(0.0f, 1.0f));
  EXPECT_EQ(b3->GetTrajectory().initial(), p1);
  EXPECT_EQ(b3->IsAlive(), true);
  EXPECT_EQ(b3->IsCreated(), true);
  EXPECT_EQ(b3->GetShooter(), &g);
}

TEST(factory_test, test_factory_gun_construction)
{
  std::unique_ptr<Gun> g1 = Factory::Instance().Create<Gun>();
  EXPECT_EQ(g1->GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g1->GetBody().leftBottomPoint().y(), -GUN_HEIGHT / 2.0f);
  EXPECT_EQ(g1->GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g1->GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g1->GetFiringRate(), GUN_FIRING_RATE);
  EXPECT_EQ(g1->IsAlive(), true);
  EXPECT_EQ(g1->IsCreated(), true);

  std::unique_ptr<Gun> g2 = Factory::Instance().Create<Gun>(Point2D(SPACE_WIDTH / 2, GUN_HEIGHT / 2.0f));
  EXPECT_EQ(g2->GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g2->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g2->GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g2->GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g2->GetFiringRate(), GUN_FIRING_RATE);
  EXPECT_EQ(g2->IsAlive(), true);
  EXPECT_EQ(g2->IsCreated(), true);

  std::unique_ptr<Gun> g3 = Factory::Instance().Create<Gun>(Point2D(SPACE_WIDTH / 2, GUN_HEIGHT / 2.0f), 100, 1.0f);
  EXPECT_EQ(g3->GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - GUN_WIDTH / 2.0f);
  EXPECT_EQ(g3->GetBody().leftBottomPoint().y(), 0.0f);
  EXPECT_EQ(g3->GetBody().Height(), GUN_HEIGHT);
  EXPECT_EQ(g3->GetBody().Width(), GUN_WIDTH);
  EXPECT_EQ(g3->GetAmmo(), 100);
  EXPECT_EQ(g3->GetFiringRate(), 1.0f);
  EXPECT_EQ(g3->IsAlive(), true);
  EXPECT_EQ(g3->IsCreated(), true);
}

TEST(factory_test, test_factory_alien_construction)
{
  std::unique_ptr<Alien> a1 = Factory::Instance().Create<Alien>();
  EXPECT_EQ(a1->GetBody().leftBottomPoint().x(), SPACE_WIDTH / 2.0f - ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a1->GetBody().leftBottomPoint().y(), SPACE_HEIGHT / 2.0f - ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a1->GetBody().rightTopPoint().x(), SPACE_WIDTH / 2.0f + ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a1->GetBody().rightTopPoint().y(), SPACE_HEIGHT / 2.0f + ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a1->GetBody().Height(), ALIEN_HEIGHT);
  EXPECT_EQ(a1->GetBody().Width(), ALIEN_WIDTH);
  EXPECT_EQ(a1->GetFiringRate(), ALIEN_FIRING_RATE);
  EXPECT_EQ(a1->IsAlive(), true);
  EXPECT_EQ(a1->IsCreated(), true);

  Point2D p2 = { 10.0f, 11.0f };
  std::unique_ptr<Alien> a2 = Factory::Instance().Create<Alien>(p2);
  EXPECT_EQ(a2->GetBody().leftBottomPoint().x(), p2.x() - ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a2->GetBody().leftBottomPoint().y(), p2.y() - ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a2->GetBody().rightTopPoint().x(), p2.x() + ALIEN_HEIGHT / 2.0f);
  EXPECT_EQ(a2->GetBody().rightTopPoint().y(), p2.y() + ALIEN_WIDTH / 2.0f);
  EXPECT_EQ(a2->GetBody().Height(), ALIEN_HEIGHT);
  EXPECT_EQ(a2->GetBody().Width(), ALIEN_WIDTH);
  EXPECT_EQ(a2->IsAlive(), true);
  EXPECT_EQ(a2->IsCreated(), true);

  Point2D p1 = {0.0f, 0.0f};
  std::unique_ptr<Alien> a3 = Factory::Instance().Create<Alien>(Box2D(p1, p2));
  EXPECT_EQ(a3->GetBody().leftBottomPoint().x(), p1.x());
  EXPECT_EQ(a3->GetBody().leftBottomPoint().y(), p1.y());
  EXPECT_EQ(a3->GetBody().rightTopPoint().x(), p2.x());
  EXPECT_EQ(a3->GetBody().rightTopPoint().y(), p2.y());
  EXPECT_EQ(a3->GetBody().Height(), p2.y() - p1.y());
  EXPECT_EQ(a3->GetBody().Width(), p2.x() - p1.x());
  EXPECT_EQ(a3->IsAlive(), true);
  EXPECT_EQ(a3->IsCreated(), true);
}
