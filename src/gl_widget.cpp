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
  setMinimumSize(SPACE_WIDTH, SPACE_HEIGHT);
  m_screenSize.setWidth(SPACE_WIDTH);
  m_screenSize.setHeight(SPACE_HEIGHT);
  setFocusPolicy(Qt::StrongFocus);
  this->setMouseTracking(true);
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

  for(int j = 0; j < NUMBER_OF_LINES; j++)
  {
    for(int i = 0; i < NUMBER_OF_ALIENS_IN_LINE; i++)
    {
      m_aliens.push_back(Factory::Instance().Create<Alien>(Point2D(i * 100.0f + 50.0f, j * 100.0f + 400.0f)));
    }
  }

  m_gun = Factory::Instance().Create<Gun>(Point2D(m_screenSize.rwidth() / 2, GUN_HEIGHT / 2));

  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_screenSize.rwidth() / 4, 200.0f)));
  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_screenSize.rwidth() / 2, 200.0f)));
  m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_screenSize.rwidth() / 4 * 3, 200.0f)));
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
  painter.end();
  ++m_frames;
  update();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);

  m_obstacles[0]->SetCoordinate(Point2D(m_screenSize.rwidth() / 4, 200.0f));
  m_obstacles[1]->SetCoordinate(Point2D(m_screenSize.rwidth() / 2, 200.0f));
  m_obstacles[2]->SetCoordinate(Point2D(m_screenSize.rwidth() / 4 * 3, 200.0f));
}

void GLWidget::Update(float elapsedSeconds)
{
  // ВСЕ ЭТО ДОБРО ВЫЗЫВАЕТ КРЭШ ПРОГРАММЫ. НУЖНО КАК-ТО ИНАЧЕ ОБРАБАТЫВАТЬ ПОПАДАНИЯ.

  /*for(int i = 0; i < m_aliens.size(); i++)
    for(int j = 0; j < m_gun_bullets.size(); j++)
      if (m_gun_bullets[j]->GetCoordinate() > m_aliens[i]->GetCoordinate() - ALIEN_WIDTH / 2 && m_gun_bullets[j]->GetCoordinate() < m_aliens[i]->GetCoordinate() + ALIEN_WIDTH / 2)
      {
        m_gun_bullets[j]->Hit(*m_aliens[i]);

        m_aliens[i].reset();
        m_aliens.erase(m_aliens.begin() + i);

        m_gun_bullets[j].reset();
        m_gun_bullets.erase(m_gun_bullets.begin() + j);
      }

  for(int i = 0; i < m_obstacles.size(); i++)
    for(int j = 0; j < m_alien_bullets.size(); j++)
      if (m_alien_bullets[j]->GetCoordinate() > m_obstacles[i]->GetCoordinate() - OBSTACLE_WIDTH / 2 && m_alien_bullets[j]->GetCoordinate() < m_obstacles[i]->GetCoordinate() + OBSTACLE_WIDTH / 2)
      {
        m_alien_bullets[j]->Hit(*m_obstacles[i]);

        m_obstacles[i].reset();
        m_obstacles.erase(m_obstacles.begin() + i);

        m_alien_bullets[j].reset();
        m_alien_bullets.erase(m_alien_bullets.begin() + j);
      }

  for(int i = 0; i < m_obstacles.size(); i++)
    for(int j = 0; j < m_gun_bullets.size(); j++)
      if (m_gun_bullets[j]->GetCoordinate() > m_obstacles[i]->GetCoordinate() - OBSTACLE_WIDTH / 2 && m_gun_bullets[j]->GetCoordinate() < m_obstacles[i]->GetCoordinate() + OBSTACLE_WIDTH / 2)
      {
        m_gun_bullets[j]->Hit(*m_obstacles[i]);

        m_obstacles[i].reset();
        m_obstacles.erase(m_obstacles.begin() + i);

        m_gun_bullets[j].reset();
        m_gun_bullets.erase(m_gun_bullets.begin() + j);
      }

  for(int j = 0; j < m_alien_bullets.size(); j++)
    if (m_alien_bullets[j]->GetCoordinate() > m_gun->GetCoordinate() - GUN_WIDTH / 2 && m_alien_bullets[j]->GetCoordinate() < m_gun->GetCoordinate() + GUN_WIDTH / 2)
    {
      m_alien_bullets[j]->Hit(*m_gun);

      m_gun.reset();

      m_alien_bullets[j].reset();
      m_alien_bullets.erase(m_alien_bullets.begin() + j);
    }*/

  if (m_time.elapsed() % 10 == 0)
  {
    random_index = std::rand()% 31;
    m_alien_bullets.push_back(Factory::Instance().Create<Bullet>(*m_aliens[random_index]));
  }

  float const kSpeed = 10.0f; // pixels per second.

  if (m_directions[kUpDirection])
    m_gun->SetY(m_gun->GetCoordinate().y() + kSpeed);
  if (m_directions[kDownDirection])
    m_gun->SetY(m_gun->GetCoordinate().y() - kSpeed);
  if (m_directions[kLeftDirection])
    m_gun->SetX(m_gun->GetCoordinate().x() - kSpeed);
  if (m_directions[kRightDirection])
    m_gun->SetX(m_gun->GetCoordinate().x() + kSpeed);
}

void GLWidget::Render()
{
  RenderStars();
  RenderBullets();
  RenderAliens();
  RenderGun();
  RenderObstacles();
}

void GLWidget::RenderAliens()
{
  if (m_aliens[m_aliens.size() - 1]->GetCoordinate().x() + ALIEN_WIDTH / 2 > m_screenSize.rwidth() || m_aliens[0]->GetCoordinate().x() - ALIEN_WIDTH / 2 < 0)
  {
    for(int i = 0; i < m_aliens.size(); ++i)
    {
      m_aliens[i]->Refract();
      m_aliens[i]->MoveDown();
    }
  }
  for(int i = 0; i < m_aliens.size(); ++i)
  {
    m_texturedRect->Render(m_textureAlien, Point2D(static_cast<int>(m_aliens[i]->Move().GetCoordinate().x()),static_cast<int>(m_aliens[i]->Move().GetCoordinate().y())), QSize(ALIEN_WIDTH, ALIEN_HEIGHT), m_screenSize);
  }
}

void GLWidget::RenderBullets()
{
  for(int i = 0; i < m_gun_bullets.size(); ++i)
  {
    m_texturedRect->Render(m_textureBullet, Point2D(static_cast<int>(m_gun_bullets[i]->Move().GetCoordinate().x()),static_cast<int>(m_gun_bullets[i]->Move().GetCoordinate().y())), QSize(BULLET_WIDTH, BULLET_HEIGHT), m_screenSize);
    if (m_gun_bullets[i]->GetCoordinate().y() > m_screenSize.rheight() || m_gun_bullets[i]->GetCoordinate().y() < 0)
    {
      m_gun_bullets[i].reset();
      m_gun_bullets.erase(m_gun_bullets.begin() + i);
    }
  }
  for(int i = 0; i < m_alien_bullets.size(); ++i)
  {
    m_texturedRect->Render(m_textureBullet, Point2D(static_cast<int>(m_alien_bullets[i]->Move().GetCoordinate().x()),static_cast<int>(m_alien_bullets[i]->Move().GetCoordinate().y())), QSize(BULLET_WIDTH, BULLET_HEIGHT), m_screenSize);
    if (m_alien_bullets[i]->GetCoordinate().y() > m_screenSize.rheight() || m_alien_bullets[i]->GetCoordinate().y() < 0)
    {
      m_alien_bullets[i].reset();
      m_alien_bullets.erase(m_alien_bullets.begin() + i);
    }
  }
}

void GLWidget::RenderGun()
{
  m_texturedRect->Render(m_textureGun, m_gun->GetCoordinate(), QSize(GUN_WIDTH, GUN_HEIGHT), m_screenSize);
}

void GLWidget::RenderObstacles()
{
  for(int i = 0; i < m_obstacles.size(); ++i)
  {
    m_texturedRect->Render(m_textureObstacle, Point2D(static_cast<int>(m_obstacles[i]->GetCoordinate().x()),static_cast<int>(m_obstacles[i]->GetCoordinate().y())), QSize(OBSTACLE_WIDTH, OBSTACLE_HEIGHT), m_screenSize);
  }
}

void GLWidget::RenderStars()
{
  for(int i = 0; i < m_stars.size(); ++i)
  {
    int star_size = 10 * sinf((m_stars[i].getT() - m_time.elapsed()) / 500.0f);
    m_texturedRect->Render(m_textureStar, Point2D(m_stars[i].getX() * m_screenSize.width(), m_stars[i].getY() * m_screenSize.height()), QSize(star_size, star_size), m_screenSize);
  }
}

void GLWidget::mousePressEvent(QMouseEvent * e)
{
  QOpenGLWidget::mousePressEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
  if (IsLeftButton(e))
  {
    m_gun_bullets.push_back(Factory::Instance().Create<Bullet>(*m_gun));
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

  //int const px = L2D(e->x());
  //int const py = L2D(e->y());
  m_gun->SetX(L2D(e->x()));
  if (IsLeftButton(e))
  {
    // ...
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

