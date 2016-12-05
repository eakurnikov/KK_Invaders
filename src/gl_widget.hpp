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


class MainWindow;

QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)
QT_FORWARD_DECLARE_CLASS(QOpenGLShader)
QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT
public:
  GLWidget(MainWindow * mw, QColor const & background);
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
  int L2D(int px) const { return px * devicePixelRatio(); }

  MainWindow * m_mainWindow;

  unsigned int m_frames = 0;
  QTime m_time;
  QColor m_background;
  QSize m_screenSize;

  TexturedRect * m_texturedRect = nullptr;

  std::array<bool, 4> m_directions = { { false, false, false, false } };

  QOpenGLTexture * m_textureStar = nullptr;
  int m_starsNumber = 50 + std::rand() % 100;
  std::vector<Star> m_stars;

  QOpenGLTexture * m_textureAlien = nullptr;
  std::vector<std::unique_ptr<Alien>> m_aliens;
  int random_index;

  QOpenGLTexture * m_textureGun = nullptr;
  std::unique_ptr<Gun> m_gun;

  QOpenGLTexture * m_textureBullet = nullptr;
  std::vector<std::unique_ptr<Bullet>> m_alien_bullets;
  std::vector<std::unique_ptr<Bullet>> m_gun_bullets;

  QOpenGLTexture * m_textureObstacle = nullptr;
  std::vector<std::unique_ptr<Obstacle>> m_obstacles;
};

#endif // GL_WIDGET_HPP

