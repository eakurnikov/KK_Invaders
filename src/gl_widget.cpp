#include "gl_widget.hpp"

#include <QPainter>
#include <QPaintEngine>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QCoreApplication>
#include <QtGui/QMouseEvent>
#include <QtGui/QGuiApplication>

#include <iostream>

#include "mainwindow.hpp"

namespace
{

int constexpr kLeftDirection = 0;
int constexpr kRightDirection = 1;
int constexpr kUpDirection = 2;
int constexpr kDownDirection = 3;

bool IsLeftButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::LeftButton;
}
bool IsLeftButton(QMouseEvent const * const e)
{
  return IsLeftButton(e->button()) || IsLeftButton(e->buttons());
}

bool IsRightButton(Qt::MouseButtons buttons)
{
  return buttons & Qt::RightButton;
}
bool IsRightButton(QMouseEvent const * const e)
{
  return IsRightButton(e->button()) || IsRightButton(e->buttons());
}

} // namespace

GLWidget::GLWidget(MainWindow * mw, QColor const & background)
  : m_mainWindow(mw)
  , m_background(background)
{
  setMinimumSize(1024, 768);
  setFocusPolicy(Qt::StrongFocus);
  //this->setMouseTracking(true); //это нужно дописать по идее, чтобы движение мыши отслеживалось, но нихрена
  //m_mainWindow->setMouseTracking(true);
  this->show();
}

GLWidget::~GLWidget()
{
  makeCurrent();
  delete m_textureAlien;
  delete m_textureBullet;
  delete m_textureGun;
  delete m_textureObstacle;
  delete m_textureStar;
  delete m_texturedRect;
  doneCurrent();
}

void GLWidget::initializeGL()
{
  initializeOpenGLFunctions();

  m_texturedRect = new TexturedRect();
  m_texturedRect->Initialize(this);

  m_textureStar = new QOpenGLTexture(QImage("data/star.png"));
  m_textureAlien = new QOpenGLTexture(QImage("data/alien.png"));
  m_textureGun = new QOpenGLTexture(QImage("data/gun.png"));
  m_textureBullet = new QOpenGLTexture(QImage("data/bullet.png"));
  m_textureObstacle = new QOpenGLTexture(QImage("data/obstacle.png"));

  m_time.start();

  for(int i = 0; i < m_starsNumber; i++)
    m_stars.push_back(Star());

  for(int j = 0; j < 3; j++)
  {
    for(int i = 0; i < 5; i++)
    {
      m_aliens.push_back(Factory::Instance().Create<Alien>(Point2D(i * 200.0f + 100.0f, j * 100.0f + 500.0f)));
    }
  }

  m_gun = Factory::Instance().Create<Gun>(Point2D(500.0f, 50.0f));

  m_bullets.push_back(Factory::Instance().Create<Bullet>(*m_gun));

  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(200.0f, 200.0f)));
  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(500.0f, 200.0f)));
  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(800.0f, 200.0f)));

  m_position = QVector2D((int)m_gun->GetCoordinate().x(), (int)m_gun->GetCoordinate().y());
}

void GLWidget::paintGL()
{
  int const elapsed = m_time.elapsed();
  Update(elapsed / 1000.0f);

  QPainter painter;
  painter.begin(this);
  painter.beginNativePainting();

  glClearColor(0, 0, 0, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glFrontFace(GL_CW);
  glCullFace(GL_BACK);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Render();

  glDisable(GL_CULL_FACE);
  glDisable(GL_BLEND);

  painter.endNativePainting();

  if (elapsed != 0)
  {
    QString framesPerSecond;
    framesPerSecond.setNum(m_frames / (elapsed / 1000.0), 'f', 2);
    painter.setPen(Qt::white);
    painter.drawText(20, 40, framesPerSecond + " fps");
  }
  painter.drawText(20, m_mainWindow->height()-100, "3");
  painter.drawText(200, m_mainWindow->height()-100, "3");
  painter.end();
  ++m_frames;
  update();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);
}

void GLWidget::Update(float elapsedSeconds)
{
  for(int i = 0; i < m_aliens.size(); i++)
      if (m_gun->GetBody().IsBoxesIntersect(m_aliens[i]->GetBody()))
      {
        m_aliens.erase(m_aliens.begin() + i);
        break; // НЕ УВЕРЕН, ЧТО ЭТО ПРАВИЛЬНО
      }

  float const kSpeed = 10.0f; // pixels per second.

  if (m_directions[kUpDirection])
    m_gun->SetCoordinate(Point2D(m_gun->GetCoordinate().x(), m_gun->GetCoordinate().y() + kSpeed));
    //m_position.setY(m_position.y() + kSpeed);
  if (m_directions[kDownDirection])
    m_gun->SetCoordinate(Point2D(m_gun->GetCoordinate().x(), m_gun->GetCoordinate().y() - kSpeed));
    //m_position.setY(m_position.y() - kSpeed);
  if (m_directions[kLeftDirection])
    m_gun->SetCoordinate(Point2D(m_gun->GetCoordinate().x() - kSpeed, m_gun->GetCoordinate().y()));
    //m_position.setX(m_position.x() - kSpeed);
  if (m_directions[kRightDirection])
    m_gun->SetCoordinate(Point2D(m_gun->GetCoordinate().x() + kSpeed, m_gun->GetCoordinate().y()));
    //m_position.setX(m_position.x() + kSpeed);
}

void GLWidget::Render()
{
  RenderStars();
  RenderAliens();
  RenderGun();
  RenderBullets();
  RenderObstacles();
}

void GLWidget::RenderAliens()
{
  for(int i = 0; i < m_aliens.size(); ++i)
  {
    m_texturedRect->Render(m_textureAlien,
                           QVector2D((int)m_aliens[i]->GetCoordinate().x(),(int)m_aliens[i]->GetCoordinate().y()),
                           QSize(static_cast<int>(ALIEN_HEIGHT), static_cast<int>(ALIEN_WIDTH)),
                           m_screenSize);
  }
}

void GLWidget::RenderBullets()
{
  m_texturedRect->Render(m_textureBullet,
                         QVector2D((int)m_bullets[0]->GetCoordinate().x(),(int)m_bullets[0]->GetCoordinate().y()),
                         QSize(static_cast<int>(BULLET_HEIGHT), static_cast<int>(BULLET_HEIGHT)),
                         m_screenSize);
}

void GLWidget::RenderGun()
{
  m_texturedRect->Render(m_textureGun,
                         QVector2D((int)m_gun->GetCoordinate().x(), (int)m_gun->GetCoordinate().y()),
                         QSize(static_cast<int>(GUN_HEIGHT), static_cast<int>(GUN_HEIGHT)),
                         m_screenSize);
}

void GLWidget::RenderObstacles()
{
  for(int i = 0; i < m_obstacles.size(); ++i)
  {
    m_texturedRect->Render(m_textureObstacle,
                           QVector2D((int)m_obstacles[i]->GetCoordinate().x(), (int)m_obstacles[i]->GetCoordinate().y()),
                           QSize(static_cast<int>(OBSTACLE_HEIGHT), static_cast<int>(OBSTACLE_HEIGHT)),
                           m_screenSize);
  }
}

void GLWidget::RenderStars()
{
  for(int i = 0; i < m_stars.size(); ++i)
  {
    int size = 10 * sinf((m_stars[i].getT() - m_time.elapsed()) / 500.0f);
    m_texturedRect->Render(m_textureStar,
                           QVector2D(m_stars[i].getX() * m_screenSize.width(), m_stars[i].getY() * m_screenSize.height()),
                           QSize(size, size),
                           m_screenSize);
  }
}

void GLWidget::mousePressEvent(QMouseEvent * e)
{
  QOpenGLWidget::mousePressEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseDoubleClickEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsRightButton(e))
  {
    // ...
  }
}

void GLWidget::mouseMoveEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseMoveEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    //m_position = static_cast<QVector2D>(e->pos());
    m_position.setX(px);
  }
}

void GLWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseReleaseEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    // ...
  }
}

void GLWidget::wheelEvent(QWheelEvent * e)
{
  QOpenGLWidget::wheelEvent(e);

  int const delta = e->delta();
  int const px = L2D(e->x());
  int const py = L2D(e->y());
  // ...
}

void GLWidget::keyPressEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = true;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = true;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = true;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = true;
}

void GLWidget::keyReleaseEvent(QKeyEvent * e)
{
  if (e->key() == Qt::Key_Up)
    m_directions[kUpDirection] = false;
  else if (e->key() == Qt::Key_Down)
    m_directions[kDownDirection] = false;
  else if (e->key() == Qt::Key_Left)
    m_directions[kLeftDirection] = false;
  else if (e->key() == Qt::Key_Right)
    m_directions[kRightDirection] = false;
}

