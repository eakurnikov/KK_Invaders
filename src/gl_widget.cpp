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

  Point2D m_start ;
  for(int k = 1; k <= NUMBER_OF_GROUPS; k++)
  {
    m_start = {k * m_screenSize.rwidth() / 4 - OBSTACLE_WIDTH * 4, 200 - OBSTACLE_HEIGHT * 2};
    for(int j = 0; j < 4; j++)
    {
      for(int i = 0; i < 8; i++)
      {
        m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_start.x() + i * OBSTACLE_WIDTH, m_start.y() + j * OBSTACLE_HEIGHT)));
      }
    }
  }
}
void GLWidget::NewLevel()
{
  m_numberOfAliens = NUMBER_OF_LINES * NUMBER_OF_ALIENS_IN_LINE;

  m_time.start();

  m_aliens.clear();
  m_obstacles.clear();
  m_gun_bullets.clear();
  m_alien_bullets.clear();
  for(int j = 0; j < NUMBER_OF_LINES; j++)
  {
    for(int i = 0; i < NUMBER_OF_ALIENS_IN_LINE; i++)
    {
      m_aliens.push_back(Factory::Instance().Create<Alien>(Point2D(i * 100.0f + 50.0f, j * 100.0f + 400.0f)));
    }
  }

  m_gun = Factory::Instance().Create<Gun>(Point2D(m_screenSize.rwidth() / 2, GUN_HEIGHT / 2));

  Point2D m_start ;
  for(int k = 1; k <= NUMBER_OF_GROUPS; k++)
  {
    m_start = {k * m_screenSize.rwidth() / 4 - OBSTACLE_WIDTH * 4, 200 - OBSTACLE_HEIGHT * 2};
    for(int j = 0; j < 4; j++)
    {
      for(int i = 0; i < 8; i++)
      {
        m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_start.x() + i * OBSTACLE_WIDTH, m_start.y() + j * OBSTACLE_HEIGHT)));
      }
    }
  }}

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
    QString totalScore;
    totalScore.setNum(m_mainWindow->getTotalScore());
    painter.drawText(m_screenSize.width()/3 - 100, 40, "Score: " + totalScore);
    QString numberOfLives;
    numberOfLives.setNum(m_gun->GetNumberOfLives());
    painter.drawText(m_screenSize.width()/2 - 100, 40, "Lives: " + numberOfLives);
    QString numberOfHP;
    numberOfHP.setNum(m_gun->GetHP());
    painter.drawText(m_screenSize.width() - 100, 40, "HP: " + numberOfHP);
  }
  painter.end();
  ++m_frames;
  update();
}

void GLWidget::resizeGL(int w, int h)
{
  m_screenSize.setWidth(w);
  m_screenSize.setHeight(h);

  m_obstacles.clear();
  Point2D m_start ;
  for(int k = 1; k <= NUMBER_OF_GROUPS; k++)
  {
    m_start = {k * m_screenSize.rwidth() / 4 - OBSTACLE_WIDTH * 4, 200 - OBSTACLE_HEIGHT * 2};
    for(int j = 0; j < 4; j++)
    {
      for(int i = 0; i < 8; i++)
      {
        m_obstacles.push_back(Factory::Instance().Create<Obstacle>(Point2D(m_start.x() + i * OBSTACLE_WIDTH, m_start.y() + j * OBSTACLE_HEIGHT)));
      }
    }
  }
}

void GLWidget::Update(float elapsedSeconds)
{
  if(!m_gun->IsAlive())
  {
    if(m_mainWindow->getGunNumberOfLives() == 0)
    {
      this->hide();
      m_mainWindow->GameOver();
    }
    else
    {
      this->hide();
      NewLevel();
      m_mainWindow->RestartLevel();
    }
  }

  if(m_numberOfAliens == 0)
  {
    this->hide();
    NewLevel();
    m_mainWindow->NewLevel();
  }

  for(int i = 0; i < m_aliens.size(); i++)
    for(int j = 0; j < m_gun_bullets.size(); j++)
      if (m_gun_bullets[j]->GetCoordinate() > m_aliens[i]->GetCoordinate() - ALIEN_WIDTH / 2 && m_gun_bullets[j]->GetCoordinate() < m_aliens[i]->GetCoordinate() + ALIEN_WIDTH / 2)
      {
        m_gun_bullets[j]->Hit(*m_aliens[i]);
        m_gun_bullets.erase(m_gun_bullets.begin() + j);
        m_mainWindow->setTotalScore(m_mainWindow->getTotalScore()+100);
        m_numberOfAliens -= 1;
        m_alienKill->play();
      }

  for(int i = 0; i < m_obstacles.size(); i++)
    for(int j = 0; j < m_alien_bullets.size(); j++)
      if (m_alien_bullets[j]->GetCoordinate() > m_obstacles[i]->GetCoordinate() - OBSTACLE_WIDTH / 2 && m_alien_bullets[j]->GetCoordinate() < m_obstacles[i]->GetCoordinate() + OBSTACLE_WIDTH / 2)
      {
        m_alien_bullets[j]->Hit(*m_obstacles[i]);
        m_alien_bullets.erase(m_alien_bullets.begin() + j);
      }

  for(int i = 0; i < m_obstacles.size(); i++)
    for(int j = 0; j < m_gun_bullets.size(); j++)
      if (m_gun_bullets[j]->GetCoordinate() > m_obstacles[i]->GetCoordinate() - OBSTACLE_WIDTH && m_gun_bullets[j]->GetCoordinate() < m_obstacles[i]->GetCoordinate() + OBSTACLE_WIDTH)
      {
        m_gun_bullets[j]->Hit(*m_obstacles[i]);
        m_gun_bullets.erase(m_gun_bullets.begin() + j);
      }

  for(int j = 0; j < m_alien_bullets.size(); j++)
    if (m_alien_bullets[j]->GetCoordinate() > m_gun->GetCoordinate() - GUN_WIDTH / 2 && m_alien_bullets[j]->GetCoordinate() < m_gun->GetCoordinate() + GUN_WIDTH / 2)
    {
      m_alien_bullets[j]->Hit(*m_gun);
      m_alien_bullets.erase(m_alien_bullets.begin() + j);
    }

  if (m_time.elapsed() % 127 < 10)
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
  for(int i = 0; i < m_aliens.size(); ++i)
  {
    if ((m_aliens[i]->GetCoordinate().x() + ALIEN_WIDTH / 2 > m_screenSize.rwidth() || m_aliens[i]->GetCoordinate().x() - ALIEN_WIDTH / 2 < 0) && m_aliens[i]->IsAlive())
    {
      for(int j = 0; j < m_aliens.size(); ++j)
      {
        m_aliens[j]->Refract();
        m_aliens[j]->MoveDown();
      }
      break;
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
    m_shot2->play();
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
  m_gun->SetX(L2D(e->x()));
}

void GLWidget::mouseReleaseEvent(QMouseEvent * e)
{
  QOpenGLWidget::mouseReleaseEvent(e);

  int const px = L2D(e->x());
  int const py = L2D(e->y());
}

void GLWidget::wheelEvent(QWheelEvent * e)
{
  QOpenGLWidget::wheelEvent(e);

  int const delta = e->delta();
  int const px = L2D(e->x());
  int const py = L2D(e->y());
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
void GLWidget::setGunHP(int const n)
{
  m_gunHP = n;
}

void GLWidget::setGunFiringRate(int const n)
{
  m_gunFiringRate = n;
}

void GLWidget::setGunSpeed(int const n)
{
  m_gunSpeed = n;
}

void GLWidget::setGunNumberOfLives(int const n)
{
  m_gunNumberOfLives = n;
}

void GLWidget::setAlienHP(int const n)
{
  m_alienHP = n;
}

void GLWidget::setAlienFiringRate(int const n)
{
  m_alienFiringRate = n;
}

void GLWidget::setAlienSpeed(int const n)
{
  m_alienSpeed = n;
}

void GLWidget::setAlienNumberInLevel(int const n)
{
  m_alienNumberInLevel = n;
}

void GLWidget::setAlienNumberOfLevels(int const n)
{
  m_alienNumberOfLevels = n;
}

void GLWidget::setBulletHP(int const n)
{
  m_bulletHP = n;
}

void GLWidget::setBulletSpeed(int const n)
{
  m_bulletSpeed = n;
}

void GLWidget::setBulletDamage(int const n)
{
  m_bulletDamage = n;
}

void GLWidget::setObstacleHP(int const n)
{
  m_obstacleHP = n;
}

void GLWidget::setObstacleNumberInGroup(int const n)
{
  m_obstacleNumberInGroup = n;
}

void GLWidget::setObstacleNumberOfGroups(int const n)
{
  m_obstacleNumberOfGroups = n;
}
