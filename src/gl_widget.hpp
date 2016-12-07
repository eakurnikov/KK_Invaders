#ifndef GL_WIDGET_HPP
#define GL_WIDGET_HPP
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTime>
#include <array>
#include <vector>
#include <list>
#include <cstdlib>
#include <cmath>
#include <memory>
#include "textured_rect.hpp"
#include "star.hpp"
#include "obstacle.hpp"
#include "bullet.hpp"
#include "factory.hpp"
#include <QSound>

class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(MainWindow * mw, QColor const & background);

  void setGunHP(int const n);
  void setGunFiringRate(int const n);
  void setGunSpeed(int const n);
  void setGunNumberOfLives(int const n);

  void setAlienHP(int const n);
  void setAlienFiringRate(int const n);
  void setAlienSpeed(int const n);
  void setAlienNumberInLevel(int const n);
  void setAlienNumberOfLevels(int const n);

  void setBulletHP(int const n);
  void setBulletSpeed(int const n);
  void setBulletDamage(int const n);

  void setObstacleHP(int const n);
  void setObstacleNumberInGroup(int const n);
  void setObstacleNumberOfGroups(int const n);



  ~GLWidget();


protected:
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void initializeGL() override;

  void Update(float elapsedSeconds);
  void Render();
  void RenderStars();
  void RenderAliens();
  void RenderBullets();
  void RenderGun();
  void RenderObstacles();

  void mousePressEvent(QMouseEvent * e) override;
  void mouseDoubleClickEvent(QMouseEvent * e) override;
  void mouseMoveEvent(QMouseEvent * e) override;
  void mouseReleaseEvent(QMouseEvent * e) override;
  void wheelEvent(QWheelEvent * e) override;
  void keyPressEvent(QKeyEvent * e) override;
  void keyReleaseEvent(QKeyEvent * e) override;

private:

  QSound * m_alienKill = new QSound("data/AlienKill.wav");
  QSound * m_obstacleKill = new QSound("data/ObstacleKill.wav");
  QSound * m_bulletKill = new QSound("data/BulletKill.wav");
  QSound * m_shot = new QSound("data/Shot.wav");
  QSound * m_shot2 = new QSound("data/Shot2.wav");

  int m_gunHP = 1;
  int m_gunFiringRate = 1;
  int m_gunSpeed = 1;
  int m_gunNumberOfLives = 1;

  int m_alienHP = 1;
  int m_alienFiringRate = 1;
  int m_alienSpeed = 1;
  int m_alienNumberInLevel = 1;
  int m_alienNumberOfLevels = 1;

  int m_bulletHP = 1;
  int m_bulletSpeed = 1;
  int m_bulletDamage = 1;

  int m_obstacleHP = 1;
  int m_obstacleNumberInGroup = 1;
  int m_obstacleNumberOfGroups = 1;

  int L2D(int px) const { return px * devicePixelRatio(); }

  MainWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;

  TexturedRect * m_texturedRect = nullptr;

  //QVector2D m_position;
  std::array<bool, 4> m_directions = { { false, false, false, false } };

  QOpenGLTexture * m_textureStar = nullptr;
  int m_starsNumber = 50 + std::rand() % 100;
  std::vector<Star> m_stars;

  QOpenGLTexture * m_textureAlien = nullptr;
  std::vector<std::unique_ptr<Alien>> m_aliens;

  QOpenGLTexture * m_textureGun = nullptr;
  std::unique_ptr<Gun> m_gun;

  QOpenGLTexture * m_textureBullet = nullptr;
  std::vector<std::unique_ptr<Bullet>> m_bullets;

  QOpenGLTexture * m_textureObstacle = nullptr;
  std::vector<std::unique_ptr<Obstacle>> m_obstacles;
};

#endif // GL_WIDGET_HPP

