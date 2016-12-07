#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QLineEdit>
#include <QWidget>
#include <QGridLayout>
#include <QSlider>
#include <QFont>
#include <QApplication>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSound>

//#include <QTimer>
#include <QThread>
#include <QOpenGLWidget>
#include "gl_widget.hpp"

class MainWindow
    : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = 0);
  void ReadJson();

  int getGunHP();
  int getGunFiringRate();
  int getGunSpeed();
  int getGunNumberOfLives();

  int getAlienHP();
  int getAlienFiringRate();
  int getAlienSpeed();
  int getAlienNumberInLevel();
  int getAlienNumberOfLevels();

  int getBulletHP();
  int getBulletSpeed();
  int getBulletDamage();

  int getObstacleHP();
  int getObstacleNumberInGroup();
  int getObstacleNumberOfGroups();

  int getTotalScore();
  int getLevel();

  void setTotalScore(int const n);
  void SetLevel(int const n);

  void ShowInfo();

  ~MainWindow();

private slots:
  void sliderMovedCustomChecked();
  void radioButtonNoobClicked();
  void radioButtonNormalClicked();
  void radioButtonProClicked();
  void WriteJson();
  void StartGame();
  void ConfigShow();
  void GameOver();
  void Ready();

private:
  GLWidget m_glw;

  int m_totalScore = 0;
  int m_level = 1;

  QSound * m_buttonClick = new QSound("data/ButtonClick.wav");

  QTimer * m_timer = nullptr;
  QGridLayout * m_layout = nullptr;
  QOpenGLWidget * m_glWidget = nullptr;

  // Начальный виджет
  QWidget * m_widgetWelcome = nullptr;

  // Начальная таблица
  QGridLayout * m_layoutWelcome = nullptr;

  // Элементы начального виджета
  QLabel * m_labelWelcome = nullptr;
  QPushButton * m_buttonConfig = nullptr;
  QPushButton * m_buttonWStart = nullptr;
  QPushButton * m_buttonExit = nullptr;

  // Информационный виджет
  QWidget * m_widgetInfo = nullptr;
  // Информационный таблица
  QGridLayout * m_layoutInfo = nullptr;
  // Элементы Информационного виджета
  // Название игры
  QLabel * m_labelGameName = nullptr;
  // Номер уровня
  QLabel * m_labelGameLevel = nullptr;
  // Счет
  QLabel * m_labelGameScore = nullptr;
  // Число жизней
  QLabel * m_labelGameLives = nullptr;
  // Кнопка запуска
  QPushButton * m_buttonReady = nullptr;

  // Последний виджет
  QWidget * m_widgetGameOver = nullptr;
  // Последняя таблица
  QGridLayout * m_layoutGameOver = nullptr;
  // Элементы последнего виджета
  QLabel * m_labelGameOver = nullptr;
  // Номер последнего уровня
  QLabel * m_labelGameOverLevel = nullptr;
  // Счет
  QLabel * m_labelGameOverScore = nullptr;


  // Центральный виджет
  QWidget * m_centralWidget = nullptr;
  // Главная таблица
  QGridLayout * m_layoutMain = nullptr;
  // Выбор режима
  QLabel * m_labelMode = nullptr;
  // Верхний виджет (выбор режима)
  QWidget * m_topWidget = nullptr;
  QHBoxLayout * m_radioLayout = nullptr;
  QButtonGroup * m_group = nullptr;
  QRadioButton * m_radioButtonNoob = nullptr;
  QRadioButton * m_radioButtonNormal = nullptr;
  QRadioButton * m_radioButtonPro = nullptr;
  QRadioButton * m_radioButtonCustom = nullptr;

  // Настройки пушки
  QWidget * m_centralWidgetGun = nullptr;
  QGridLayout * m_layoutGun = nullptr;
  QLabel * m_labelGun = nullptr;
  QLabel * m_labelGunHP = nullptr;
  QSlider * m_sliderGunHP = nullptr;
  QLabel * m_labelValueGunHP = nullptr;
  QLabel * m_labelGunFiringRate = nullptr;
  QSlider * m_sliderGunFiringRate = nullptr;
  QLabel * m_labelValueGunFiringRate = nullptr;
  QLabel * m_labelGunSpeed = nullptr;
  QSlider * m_sliderGunSpeed  = nullptr;
  QLabel * m_labelValueGunSpeed = nullptr;
  QLabel * m_labelGunNumberOfLives = nullptr;
  QSlider * m_sliderGunNumberOfLives  = nullptr;
  QLabel * m_labelValueGunNumberOfLives = nullptr;

  // Настройки пришельцев
  QWidget * m_centralWidgetAlien = nullptr;
  QGridLayout * m_layoutAlien = nullptr;
  QLabel * m_labelAlien = nullptr;
  QLabel * m_labelAlienHP = nullptr;
  QSlider * m_sliderAlienHP = nullptr;
  QLabel * m_labelValueAlienHP = nullptr;
  QLabel * m_labelAlienFiringRate = nullptr;
  QSlider * m_sliderAlienFiringRate = nullptr;
  QLabel * m_labelValueAlienFiringRate = nullptr;
  QLabel * m_labelAlienSpeed = nullptr;
  QSlider * m_sliderAlienSpeed = nullptr;
  QLabel * m_labelValueAlienSpeed = nullptr;
  QLabel * m_labelAlienNumberInLevel = nullptr;
  QSlider * m_sliderAlienNumberInLevel = nullptr;
  QLabel * m_labelValueAlienNumberInLevel = nullptr;
  QLabel * m_labelAlienNumberOfLevels = nullptr;
  QSlider * m_sliderAlienNumberOfLevels = nullptr;
  QLabel * m_labelValueAlienNumberOfLevels = nullptr;

  // Настройки пули
  QWidget * m_centralWidgetBullet = nullptr;
  QGridLayout * m_layoutBullet = nullptr;
  QLabel * m_labelBullet = nullptr;
  QLabel * m_labelBulletHP = nullptr;
  QSlider * m_sliderBulletHP = nullptr;
  QLabel * m_labelValueBulletHP = nullptr;
  QLabel * m_labelBulletSpeed = nullptr;
  QSlider * m_sliderBulletSpeed = nullptr;
  QLabel * m_labelValueBulletSpeed = nullptr;
  QLabel * m_labelBulletDamage = nullptr;
  QSlider * m_sliderBulletDamage = nullptr;
  QLabel * m_labelValueBulletDamage = nullptr;

  // Настройки препятствий
  QWidget * m_centralWidgetObstacle = nullptr;
  QGridLayout * m_layoutObstacle = nullptr;
  QLabel * m_labelObstacle = nullptr;
  QLabel * m_labelObstacleHP = nullptr;
  QSlider * m_sliderObstacleHP = nullptr;
  QLabel * m_labelValueObstacleHP = nullptr;
  QLabel * m_labelObstacleNumberInGroup = nullptr;
  QSlider * m_sliderObstacleNumberInGroup  = nullptr;
  QLabel * m_labelValueObstacleNumberInGroup = nullptr;
  QLabel * m_labelObstacleNumberOfGroups = nullptr;
  QSlider * m_sliderObstacleNumberOfGroups = nullptr;
  QLabel * m_labelValueObstacleNumberOfGroups = nullptr;

  // Нижний виджет
  QWidget * m_bottomWidget = nullptr;
  QHBoxLayout * m_bottomLayout = nullptr;
  QPushButton * m_buttonStart = nullptr;
};

