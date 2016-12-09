#include "mainwindow.hpp"
#include "defaultvalues.hpp"
#include <json/json.h>
#include <json/writer.h>
#include <json/reader.h>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), m_glw(this, QColor(255,1,1,1))
{
  // Изменение размеров окна
  this->resize(800, 800);

  // Глобальная настройка шрифтов
  QApplication::setFont(QFont("Courier", 14, QFont::Bold, false));

  // Начальный виджет
  m_widgetWelcome = new QWidget(this);
  m_widgetWelcome->setStyleSheet("background-color:black;");
  setCentralWidget(m_widgetWelcome);

  // Начальная таблица
  m_layoutWelcome = new QGridLayout(m_widgetWelcome);

  // Элементы начального виджета
  m_labelWelcome = new QLabel("Welcome to KK Invaders", m_widgetWelcome);
  m_labelWelcome->setAlignment(Qt::AlignCenter);
  QPixmap pixmapWelcome("data/logo.png");
  m_labelWelcome->setPixmap(pixmapWelcome.scaled(400, 400, Qt::IgnoreAspectRatio, Qt::FastTransformation));

  m_buttonConfig = new QPushButton("Настройки");
  m_buttonConfig->setStyleSheet("background-color:white;");
  m_buttonWStart = new QPushButton("Начать");
  m_buttonWStart->setStyleSheet("background-color:white;");
  m_buttonExit = new QPushButton("Выход");
  m_buttonExit->setStyleSheet("background-color:white;");

  // Размещение в начальной таблице
  m_layoutWelcome->addWidget(m_labelWelcome, 0, 0, 1, 2);
  m_layoutWelcome->addWidget(m_buttonConfig, 1, 0, 1, 2);
  m_layoutWelcome->addWidget(m_buttonWStart, 2, 0);
  m_layoutWelcome->addWidget(m_buttonExit, 2, 1);


  // Информационный виджет
  m_widgetInfo = new QWidget(this);
  m_widgetInfo->setStyleSheet("background-color:black;");

  // Информационный таблица
  m_layoutInfo = new QGridLayout(m_widgetInfo);

  // Элементы Информационного виджета
  // Название игры
  m_labelGameName = new QLabel("KK Invaders", m_widgetInfo);
  m_labelGameName->setAlignment(Qt::AlignCenter);
  m_labelGameName->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameName->setStyleSheet("QLabel {color : White; }");
  QPixmap pixmap("data/your-empire-needs-you.png");
  m_labelGameName->setPixmap(pixmap.scaled(600, 600, Qt::IgnoreAspectRatio, Qt::FastTransformation));


  // Номер уровня
  m_labelGameLevel = new QLabel("Level:", m_widgetInfo);
  m_labelGameLevel->setAlignment(Qt::AlignCenter);
  m_labelGameLevel->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameLevel->setStyleSheet("QLabel {color : White; }");

  m_labelGameLevelValue = new QLabel("1", m_widgetInfo);
  m_labelGameLevelValue->setAlignment(Qt::AlignCenter);
  m_labelGameLevelValue->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameLevelValue->setStyleSheet("QLabel {color : White; }");

  // Счет
  m_labelGameScore = new QLabel("Score:", m_widgetInfo);
  m_labelGameScore->setAlignment(Qt::AlignCenter);
  m_labelGameScore->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameScore->setStyleSheet("QLabel {color : White; }");

  m_labelGameScoreValue = new QLabel("0", m_widgetInfo);
  m_labelGameScoreValue->setAlignment(Qt::AlignCenter);
  m_labelGameScoreValue->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameScoreValue->setStyleSheet("QLabel {color : White; }");

  // Число жизней
  m_labelGameLives = new QLabel("Lives:", m_widgetInfo);
  m_labelGameLives->setAlignment(Qt::AlignCenter);
  m_labelGameLives->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameLives->setStyleSheet("QLabel {color : White; }");

  m_labelGameLivesValue = new QLabel("1", m_widgetInfo);
  m_labelGameLivesValue->setAlignment(Qt::AlignCenter);
  m_labelGameLivesValue->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameLivesValue->setStyleSheet("QLabel {color : White; }");

  // Кнопка запуска
  m_buttonReady = new QPushButton("Готов!");
  m_buttonReady->setStyleSheet("background-color:white;");

  // Размещение в информационной таблице
  m_layoutInfo->addWidget(m_labelGameName, 1, 0, 1, 2);
  m_layoutInfo->addWidget(m_labelGameLevel, 2, 0);
  m_layoutInfo->addWidget(m_labelGameLevelValue, 2, 1);
  m_layoutInfo->addWidget(m_labelGameScore, 3, 0);
  m_layoutInfo->addWidget(m_labelGameScoreValue, 3, 1);
  m_layoutInfo->addWidget(m_labelGameLives, 4, 0);
  m_layoutInfo->addWidget(m_labelGameLivesValue, 4, 1);
  m_layoutInfo->addWidget(m_buttonReady, 5, 0, 1, 2);

  // Последний виджет
  m_widgetGameOver = new QWidget(this);
  m_widgetGameOver->setStyleSheet("background-color:black;");

  // Последняя таблица
  m_layoutGameOver = new QGridLayout(m_widgetGameOver);

  // Элементы последнего виджета
  m_labelGameOver = new QLabel("Game Over", m_widgetGameOver);
  m_labelGameOver->setAlignment(Qt::AlignCenter);
  QPixmap pixmapGameOver("data/you-have-failed-your-empire.png");
  m_labelGameOver->setPixmap(pixmapGameOver.scaled(600, 600, Qt::IgnoreAspectRatio, Qt::FastTransformation));



  // Номер последнего уровня
  m_labelGameOverLevel = new QLabel("Last Level:", m_widgetGameOver);
  m_labelGameOverLevel->setAlignment(Qt::AlignCenter);
  m_labelGameOverLevel->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameOverLevel->setStyleSheet("QLabel {color : White; }");

  m_labelGameOverLevelValue = new QLabel("1", m_widgetGameOver);
  m_labelGameOverLevelValue->setAlignment(Qt::AlignCenter);
  m_labelGameOverLevelValue->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameOverLevelValue->setStyleSheet("QLabel {color : White; }");

  // Счет
  m_labelGameOverScore = new QLabel("Score:", m_widgetGameOver);
  m_labelGameOverScore->setAlignment(Qt::AlignCenter);
  m_labelGameOverScore->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameOverScore->setStyleSheet("QLabel {color : White; }");

  m_labelGameOverScoreValue = new QLabel("0", m_widgetGameOver);
  m_labelGameOverScoreValue->setAlignment(Qt::AlignCenter);
  m_labelGameOverScoreValue->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelGameOverScoreValue->setStyleSheet("QLabel {color : White; }");

  // Размещение в последней таблице
  m_layoutGameOver->addWidget(m_labelGameOver, 1, 0, 1, 2);
  m_layoutGameOver->addWidget(m_labelGameOverLevel, 2, 0);
  m_layoutGameOver->addWidget(m_labelGameOverLevelValue, 2, 1);
  m_layoutGameOver->addWidget(m_labelGameOverScore, 3, 0);
  m_layoutGameOver->addWidget(m_labelGameOverScoreValue, 3, 1);


  // Центральный виджет
  m_centralWidget = new QWidget(this);
  m_centralWidget->setStyleSheet("background-color:black;");

  // Главная таблица
  m_layoutMain = new QGridLayout(m_centralWidget);

  // Выбор режима
  m_labelMode = new QLabel("Настройте вручную или выберите один из режимов", m_centralWidget);
  m_labelMode->setAlignment(Qt::AlignCenter);
  m_labelMode->setFont(QFont("Courier", 16, QFont::Bold, false));
  m_labelMode->setStyleSheet("QLabel {color : White; }");

  // Верхний виджет (выбор режима)
  m_topWidget = new QWidget(m_centralWidget);
  m_topWidget->setStyleSheet("background-color:black;");
  m_radioLayout = new QHBoxLayout(m_topWidget);
  m_group = new QButtonGroup(m_topWidget);
  m_radioButtonNoob = new QRadioButton("NOOB", m_topWidget);
  m_radioButtonNormal = new QRadioButton("NORMAL", m_topWidget);
  m_radioButtonPro = new QRadioButton("PRO", m_topWidget);
  m_radioButtonCustom = new QRadioButton("CUSTOM", m_topWidget);
  m_radioButtonNoob->setStyleSheet("QRadioButton {color : Red; }");
  m_radioButtonNormal->setStyleSheet("QRadioButton {color : Red; }");
  m_radioButtonPro->setStyleSheet("QRadioButton {color : Red; }");
  m_radioButtonCustom->setStyleSheet("QRadioButton {color : Red; }");

  m_radioButtonCustom->setChecked(true);
  m_group->addButton(m_radioButtonNoob);
  m_group->addButton(m_radioButtonNormal);
  m_group->addButton(m_radioButtonPro);
  m_group->addButton(m_radioButtonCustom);
  m_radioLayout->addWidget(m_radioButtonNoob);
  m_radioLayout->addWidget(m_radioButtonNormal);
  m_radioLayout->addWidget(m_radioButtonPro);
  m_radioLayout->addWidget(m_radioButtonCustom);

  // Настройки пушки
  m_centralWidgetGun = new QWidget(m_centralWidget);
  m_centralWidgetGun->setStyleSheet("background-color:black;");
  m_layoutGun = new QGridLayout(m_centralWidgetGun);

  m_labelGun = new QLabel("Настройки пушки", m_centralWidgetGun);
  m_labelGun->setStyleSheet("QLabel {color : Red; }");
  m_labelGun->setAlignment(Qt::AlignCenter);
  m_labelGunHP = new QLabel("HP:", m_centralWidgetGun);
  m_labelGunHP->setStyleSheet("QLabel {color : White; }");
  m_sliderGunHP = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunHP->setRange(GUN_HP_MIN, GUN_HP_MAX);
  m_labelValueGunHP = new QLabel(std::to_string(m_sliderGunHP->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunHP->setAlignment(Qt::AlignRight);
  m_labelValueGunHP->setStyleSheet("QLabel {color : White; }");
  connect(m_sliderGunHP, SIGNAL(valueChanged(int)), m_labelValueGunHP, SLOT(setNum(int)));

  m_labelGunFiringRate = new QLabel("Скорость перезарядки:", m_centralWidgetGun);
  m_labelGunFiringRate->setStyleSheet("QLabel {color : White; }");
  m_sliderGunFiringRate = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunFiringRate->setRange(GUN_FIRING_RATE_MIN, GUN_FIRING_RATE_MAX);
  m_labelValueGunFiringRate = new QLabel(std::to_string(m_sliderGunFiringRate->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunFiringRate->setStyleSheet("QLabel {color : White; }");
  m_labelValueGunFiringRate->setAlignment(Qt::AlignRight);
  connect(m_sliderGunFiringRate, SIGNAL(valueChanged(int)), m_labelValueGunFiringRate, SLOT(setNum(int)));

  m_labelGunSpeed = new QLabel("Скорость:", m_centralWidgetGun);
  m_labelGunSpeed ->setStyleSheet("QLabel {color : White; }");
  m_sliderGunSpeed  = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunSpeed->setRange(GUN_SPEED_MIN, GUN_SPEED_MAX);
  m_labelValueGunSpeed = new QLabel(std::to_string(m_sliderGunSpeed->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunSpeed->setStyleSheet("QLabel {color : White; }");
  m_labelValueGunSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderGunSpeed, SIGNAL(valueChanged(int)), m_labelValueGunSpeed, SLOT(setNum(int)));

  m_labelGunNumberOfLives = new QLabel("Начальное число жизней:", m_centralWidgetGun);
  m_labelGunNumberOfLives->setStyleSheet("QLabel {color : White; }");
  m_sliderGunNumberOfLives  = new QSlider(Qt::Horizontal, m_centralWidgetGun);
  m_sliderGunNumberOfLives->setRange(GUN_NUMBER_OF_LIVES_MIN, GUN_NUMBER_OF_LIVES_MAX);
  m_labelValueGunNumberOfLives = new QLabel(std::to_string(m_sliderGunNumberOfLives->value()).c_str(), m_centralWidgetGun);
  m_labelValueGunNumberOfLives->setStyleSheet("QLabel {color : White; }");
  m_labelValueGunNumberOfLives->setAlignment(Qt::AlignRight);
  connect(m_sliderGunNumberOfLives, SIGNAL(valueChanged(int)), m_labelValueGunNumberOfLives, SLOT(setNum(int)));

  m_layoutGun->addWidget(m_labelGun, 0, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunHP, 1, 0);
  m_layoutGun->addWidget(m_labelValueGunHP, 1, 1);
  m_layoutGun->addWidget(m_sliderGunHP, 2, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunFiringRate, 3, 0);
  m_layoutGun->addWidget(m_labelValueGunFiringRate, 3, 1);
  m_layoutGun->addWidget(m_sliderGunFiringRate, 4, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunSpeed, 5, 0);
  m_layoutGun->addWidget(m_labelValueGunSpeed, 5, 1);
  m_layoutGun->addWidget(m_sliderGunSpeed, 6, 0, 1, 2);
  m_layoutGun->addWidget(m_labelGunNumberOfLives, 7, 0);
  m_layoutGun->addWidget(m_labelValueGunNumberOfLives, 7, 1);
  m_layoutGun->addWidget(m_sliderGunNumberOfLives, 8, 0, 1, 2);

  // Настройки пришельцев
  m_centralWidgetAlien = new QWidget(m_centralWidget);
  m_centralWidgetAlien->setStyleSheet("background-color:black;");
  m_layoutAlien = new QGridLayout(m_centralWidgetAlien);

  m_labelAlien = new QLabel("Настройки пришельцов", m_centralWidgetAlien);
  m_labelAlien->setStyleSheet("QLabel {color : Red; }");
  m_labelAlien->setAlignment(Qt::AlignCenter);
  m_labelAlienHP = new QLabel("HP:", m_centralWidgetAlien);
  m_labelAlienHP ->setStyleSheet("QLabel {color : White; }");
  m_sliderAlienHP = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienHP->setRange(ALIEN_HP_MIN, ALIEN_HP_MAX);
  m_labelValueAlienHP = new QLabel(std::to_string(m_sliderAlienHP->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienHP->setStyleSheet("QLabel {color : White; }");
  m_labelValueAlienHP->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienHP, SIGNAL(valueChanged(int)), m_labelValueAlienHP, SLOT(setNum(int)));

  m_labelAlienFiringRate = new QLabel("Скорость перезарядки:", m_centralWidgetAlien);
  m_labelAlienFiringRate->setStyleSheet("QLabel {color : White; }");
  m_sliderAlienFiringRate = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienFiringRate->setRange(ALIEN_FIRING_RATE_MIN, ALIEN_FIRING_RATE_MAX);
  m_labelValueAlienFiringRate = new QLabel(std::to_string(m_sliderAlienFiringRate->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienFiringRate->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienFiringRate, SIGNAL(valueChanged(int)), m_labelValueAlienFiringRate, SLOT(setNum(int)));

  m_labelAlienSpeed = new QLabel("Скорость:", m_centralWidgetAlien);
  m_labelAlienSpeed->setStyleSheet("QLabel {color : White; }");
  m_sliderAlienSpeed = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienSpeed->setRange(ALIEN_SPEED_MIN, ALIEN_SPEED_MAX);
  m_labelValueAlienSpeed = new QLabel(std::to_string(m_sliderAlienSpeed->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienSpeed->setStyleSheet("QLabel {color : White; }");
  m_labelValueAlienSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienSpeed, SIGNAL(valueChanged(int)), m_labelValueAlienSpeed, SLOT(setNum(int)));

  m_labelAlienNumberInLevel = new QLabel("Число пришельцев на уровне:", m_centralWidgetAlien);
  m_labelAlienNumberInLevel->setStyleSheet("QLabel {color : White; }");
  m_sliderAlienNumberInLevel = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienNumberInLevel->setRange(ALIEN_NUMBER_IN_LEVEL_MIN, ALIEN_NUMBER_IN_LEVEL_MAX);
  m_labelValueAlienNumberInLevel = new QLabel(std::to_string(m_sliderAlienNumberInLevel->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienNumberInLevel->setStyleSheet("QLabel {color : White; }");
  m_labelValueAlienNumberInLevel->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienNumberInLevel, SIGNAL(valueChanged(int)), m_labelValueAlienNumberInLevel, SLOT(setNum(int)));

  m_labelAlienNumberOfLevels = new QLabel("Число уровней:", m_centralWidgetAlien);
  m_labelAlienNumberOfLevels->setStyleSheet("QLabel {color : White; }");
  m_sliderAlienNumberOfLevels = new QSlider(Qt::Horizontal, m_centralWidgetAlien);
  m_sliderAlienNumberOfLevels->setRange(ALIEN_NUMBER_OF_LEVELS_MIN, ALIEN_NUMBER_OF_LEVELS_MAX);
  m_labelValueAlienNumberOfLevels = new QLabel(std::to_string(m_sliderAlienNumberOfLevels->value()).c_str(), m_centralWidgetAlien);
  m_labelValueAlienNumberOfLevels->setStyleSheet("QLabel {color : White; }");
  m_labelValueAlienNumberOfLevels->setAlignment(Qt::AlignRight);
  connect(m_sliderAlienNumberOfLevels, SIGNAL(valueChanged(int)), m_labelValueAlienNumberOfLevels, SLOT(setNum(int)));

  m_layoutAlien->addWidget(m_labelAlien, 0, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienHP, 1, 0);
  m_layoutAlien->addWidget(m_labelValueAlienHP, 1, 1);
  m_layoutAlien->addWidget(m_sliderAlienHP, 2, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienFiringRate, 3, 0);
  m_layoutAlien->addWidget(m_labelValueAlienFiringRate, 3, 1);
  m_layoutAlien->addWidget(m_sliderAlienFiringRate, 4, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienSpeed, 5, 0);
  m_layoutAlien->addWidget(m_labelValueAlienSpeed, 5, 1);
  m_layoutAlien->addWidget(m_sliderAlienSpeed, 6, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienNumberInLevel, 7, 0);
  m_layoutAlien->addWidget(m_labelValueAlienNumberInLevel, 7, 1);
  m_layoutAlien->addWidget(m_sliderAlienNumberInLevel, 8, 0, 1, 2);
  m_layoutAlien->addWidget(m_labelAlienNumberOfLevels, 9, 0);
  m_layoutAlien->addWidget(m_labelValueAlienNumberOfLevels, 9, 1);
  m_layoutAlien->addWidget(m_sliderAlienNumberOfLevels, 10, 0, 1, 2);

  // Настройки пули
  m_centralWidgetBullet = new QWidget(m_centralWidget);
  m_centralWidgetBullet->setStyleSheet("background-color:black;");
  m_layoutBullet = new QGridLayout(m_centralWidgetBullet);

  m_labelBullet = new QLabel("Настройки пуль", m_centralWidgetBullet);
  m_labelBullet->setStyleSheet("QLabel {color : Red; }");
  m_labelBullet->setAlignment(Qt::AlignCenter);
  m_labelBulletHP = new QLabel("HP:", m_centralWidgetBullet);
  m_labelBulletHP->setStyleSheet("QLabel {color : White; }");
  m_sliderBulletHP = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletHP->setRange(BULLET_HP_MIN, BULLET_HP_MAX);
  m_labelValueBulletHP = new QLabel(std::to_string(m_sliderBulletHP->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletHP->setStyleSheet("QLabel {color : White; }");
  m_labelValueBulletHP->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletHP, SIGNAL(valueChanged(int)), m_labelValueBulletHP, SLOT(setNum(int)));

  m_labelBulletSpeed = new QLabel("Скорость:", m_centralWidgetBullet);
  m_labelBulletSpeed->setStyleSheet("QLabel {color : White; }");
  m_sliderBulletSpeed = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletSpeed->setRange(BULLET_SPEED_MIN, BULLET_SPEED_MAX);
  m_labelValueBulletSpeed = new QLabel(std::to_string(m_sliderBulletSpeed->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletSpeed->setStyleSheet("QLabel {color : White; }");
  m_labelValueBulletSpeed->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletSpeed, SIGNAL(valueChanged(int)), m_labelValueBulletSpeed, SLOT(setNum(int)));

  m_labelBulletDamage = new QLabel("Урон:", m_centralWidgetBullet);
  m_labelBulletDamage->setStyleSheet("QLabel {color : White; }");
  m_sliderBulletDamage = new QSlider(Qt::Horizontal, m_centralWidgetBullet);
  m_sliderBulletDamage->setRange(BULLET_DAMAGE_MIN, BULLET_DAMAGE_MAX);
  m_labelValueBulletDamage = new QLabel(std::to_string(m_sliderBulletDamage->value()).c_str(), m_centralWidgetBullet);
  m_labelValueBulletDamage->setStyleSheet("QLabel {color : White; }");
  m_labelValueBulletDamage->setAlignment(Qt::AlignRight);
  connect(m_sliderBulletDamage, SIGNAL(valueChanged(int)), m_labelValueBulletDamage, SLOT(setNum(int)));

  m_layoutBullet->addWidget(m_labelBullet, 0, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletHP, 1, 0);
  m_layoutBullet->addWidget(m_labelValueBulletHP, 1, 1);
  m_layoutBullet->addWidget(m_sliderBulletHP, 2, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletSpeed, 3, 0);
  m_layoutBullet->addWidget(m_labelValueBulletSpeed, 3, 1);
  m_layoutBullet->addWidget(m_sliderBulletSpeed, 4, 0, 1, 2);
  m_layoutBullet->addWidget(m_labelBulletDamage, 5, 0);
  m_layoutBullet->addWidget(m_labelValueBulletDamage, 5, 1);
  m_layoutBullet->addWidget(m_sliderBulletDamage, 6, 0, 1, 2);

  // Настройки препятствий
  m_centralWidgetObstacle = new QWidget(m_centralWidget);
  m_centralWidgetObstacle->setStyleSheet("background-color:black;");
  m_layoutObstacle = new QGridLayout(m_centralWidgetObstacle);

  m_labelObstacle = new QLabel("Настройки препятствий", m_centralWidgetObstacle);
  m_labelObstacle->setStyleSheet("QLabel {color : Red; }");
  m_labelObstacle->setAlignment(Qt::AlignCenter);
  m_labelObstacleHP = new QLabel("HP:", m_centralWidgetObstacle);
  m_labelObstacleHP->setStyleSheet("QLabel {color : White; }");
  m_sliderObstacleHP = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleHP->setRange(OBSTACLE_HP_MIN, OBSTACLE_HP_MAX);
  m_labelValueObstacleHP = new QLabel(std::to_string(m_sliderObstacleHP->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleHP->setStyleSheet("QLabel {color : White; }");
  m_labelValueObstacleHP->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleHP, SIGNAL(valueChanged(int)), m_labelValueObstacleHP, SLOT(setNum(int)));

  m_labelObstacleNumberInGroup = new QLabel("Число препятствий в группе:", m_centralWidgetObstacle);
  m_labelObstacleNumberInGroup->setStyleSheet("QLabel {color : White; }");
  m_sliderObstacleNumberInGroup  = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleNumberInGroup->setRange(OBSTACLE_NUMBER_IN_GROUP_MIN, OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_labelValueObstacleNumberInGroup = new QLabel(std::to_string(m_sliderObstacleNumberInGroup->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleNumberInGroup->setStyleSheet("QLabel {color : White; }");
  m_labelValueObstacleNumberInGroup->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleNumberInGroup, SIGNAL(valueChanged(int)), m_labelValueObstacleNumberInGroup, SLOT(setNum(int)));

  m_labelObstacleNumberOfGroups = new QLabel("Число групп:", m_centralWidgetObstacle);
  m_labelObstacleNumberOfGroups->setStyleSheet("QLabel {color : White; }");
  m_sliderObstacleNumberOfGroups = new QSlider(Qt::Horizontal, m_centralWidgetObstacle);
  m_sliderObstacleNumberOfGroups->setRange(OBSTACLE_NUMBER_OF_GROUPS_MIN, OBSTACLE_NUMBER_OF_GROUPS_MAX);
  m_labelValueObstacleNumberOfGroups = new QLabel(std::to_string(m_sliderObstacleNumberOfGroups->value()).c_str(), m_centralWidgetObstacle);
  m_labelValueObstacleNumberOfGroups->setStyleSheet("QLabel {color : White; }");
  m_labelValueObstacleNumberOfGroups->setAlignment(Qt::AlignRight);
  connect(m_sliderObstacleNumberOfGroups, SIGNAL(valueChanged(int)), m_labelValueObstacleNumberOfGroups, SLOT(setNum(int)));

  m_layoutObstacle->addWidget(m_labelObstacle, 0, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleHP, 1, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleHP, 1, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleHP, 2, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleNumberInGroup, 3, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleNumberInGroup, 3, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleNumberInGroup, 4, 0, 1, 2);
  m_layoutObstacle->addWidget(m_labelObstacleNumberOfGroups, 5, 0);
  m_layoutObstacle->addWidget(m_labelValueObstacleNumberOfGroups, 5, 1);
  m_layoutObstacle->addWidget(m_sliderObstacleNumberOfGroups, 6, 0, 1, 2);

  // Нижний виджет
  m_bottomWidget = new QWidget(m_centralWidget);
  m_bottomWidget->setStyleSheet("background-color:black;");
  m_bottomLayout = new QHBoxLayout(m_bottomWidget);
  m_buttonStart = new QPushButton("Начать");
  m_buttonStart->setStyleSheet("background-color:white;");

  m_bottomLayout->addWidget(m_buttonStart);

  // Размещение в главной таблице
  m_layoutMain->addWidget(m_labelMode, 0, 0, 1, 2);
  m_layoutMain->addWidget(m_topWidget, 1, 0, 1, 2);
  m_layoutMain->addWidget(m_centralWidgetGun, 2, 0);
  m_layoutMain->addWidget(m_centralWidgetAlien, 2, 1);
  m_layoutMain->addWidget(m_centralWidgetBullet, 3, 0);
  m_layoutMain->addWidget(m_centralWidgetObstacle, 3, 1);

  m_layoutMain->addWidget(m_bottomWidget, 4, 0, 1, 2);

  // Настройка режимов
  connect(m_radioButtonNoob, SIGNAL(clicked(bool)), this, SLOT(radioButtonNoobClicked()));
  connect(m_radioButtonNormal, SIGNAL(clicked(bool)), this, SLOT(radioButtonNormalClicked()));
  connect(m_radioButtonPro, SIGNAL(clicked(bool)), this, SLOT(radioButtonProClicked()));

  connect(m_sliderGunHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunFiringRate, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderGunNumberOfLives, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderAlienHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienFiringRate, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienNumberInLevel, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderAlienNumberOfLevels, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderBulletHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderBulletSpeed, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderBulletDamage, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_sliderObstacleHP, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderObstacleNumberInGroup, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));
  connect(m_sliderObstacleNumberOfGroups, SIGNAL(valueChanged(int)), this, SLOT(sliderMovedCustomChecked()));

  connect(m_buttonStart, SIGNAL(clicked(bool)), m_buttonClick, SLOT(play()));
  connect(m_buttonStart, SIGNAL(clicked(bool)), this, SLOT(WriteJson()));
  connect(m_buttonStart, SIGNAL(clicked(bool)), this, SLOT(StartGame()));

  // Коннекты начального виджета
  connect(m_buttonConfig, SIGNAL(clicked(bool)), m_buttonClick, SLOT(play()));
  connect(m_buttonConfig, SIGNAL(clicked(bool)), this, SLOT(ConfigShow()));

  connect(m_buttonWStart, SIGNAL(clicked(bool)), m_buttonClick, SLOT(play()));
  connect(m_buttonWStart, SIGNAL(clicked(bool)), this, SLOT(StartGame()));

  connect(m_buttonExit, SIGNAL(clicked(bool)), m_buttonClick, SLOT(play()));
  connect(m_buttonExit, SIGNAL(clicked(bool)), this, SLOT(close()));


  // Коннекты информационного виджета
  connect(m_buttonReady, SIGNAL(clicked(bool)), m_buttonClick, SLOT(play()));
  connect(m_buttonReady, SIGNAL(clicked(bool)), this, SLOT(Ready()));
  connect(m_sliderGunNumberOfLives, SIGNAL(valueChanged(int)), m_labelGameLivesValue, SLOT(setNum(int)));

}
void MainWindow::sliderMovedCustomChecked()
{
  m_radioButtonCustom->setChecked(true);
}

void MainWindow::radioButtonNoobClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MAX);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MAX);
  m_sliderGunSpeed->setValue(GUN_SPEED_MAX);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MAX);

  m_sliderAlienHP->setValue(ALIEN_HP_MIN);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MIN);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MIN);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MIN);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MIN);

  m_sliderBulletHP->setValue(BULLET_HP_MIN);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MIN);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MIN);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

// TODO: Взять настройки из оригнальной игры
void MainWindow::radioButtonNormalClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MIN);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MIN);
  m_sliderGunSpeed->setValue(GUN_SPEED_MIN);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MIN);

  m_sliderAlienHP->setValue(ALIEN_HP_MIN);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MIN);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MIN);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MIN);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MIN);

  m_sliderBulletHP->setValue(BULLET_HP_MIN);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MIN);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MIN);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

void MainWindow::radioButtonProClicked()
{
  m_sliderGunHP->setValue(GUN_HP_MIN);
  m_sliderGunFiringRate->setValue(GUN_FIRING_RATE_MIN);
  m_sliderGunSpeed->setValue(GUN_SPEED_MIN);
  m_sliderGunNumberOfLives->setValue(GUN_NUMBER_OF_LIVES_MIN);

  m_sliderAlienHP->setValue(ALIEN_HP_MAX);
  m_sliderAlienFiringRate->setValue(ALIEN_FIRING_RATE_MAX);
  m_sliderAlienSpeed->setValue(ALIEN_SPEED_MAX);
  m_sliderAlienNumberInLevel->setValue(ALIEN_NUMBER_IN_LEVEL_MAX);
  m_sliderAlienNumberOfLevels->setValue(ALIEN_NUMBER_OF_LEVELS_MAX);

  m_sliderBulletHP->setValue(BULLET_HP_MAX);
  m_sliderBulletSpeed->setValue(BULLET_SPEED_MAX);
  m_sliderBulletDamage->setValue(BULLET_DAMAGE_MAX);

  m_sliderObstacleHP->setValue(OBSTACLE_HP_MAX);
  m_sliderObstacleNumberInGroup->setValue(OBSTACLE_NUMBER_IN_GROUP_MAX);
  m_sliderObstacleNumberOfGroups->setValue(OBSTACLE_NUMBER_OF_GROUPS_MAX);
}

void MainWindow::WriteJson()
{
  Json::Value settings;
  auto & root = settings["settings"];
  root["aliensCount"] = 100;
  root["GunHP"] = m_sliderGunHP->value();
  root["GunFiringRate"] = m_sliderGunFiringRate->value();
  root["GunSpeed"] = m_sliderGunSpeed->value();
  root["GunNumberOfLives"] = m_sliderGunNumberOfLives->value();
  root["AlienHP"] = m_sliderAlienHP->value();
  root["AlienFiringRate"] = m_sliderAlienFiringRate->value();
  root["AlienSpeed"] = m_sliderAlienSpeed->value();
  root["AlienNumberInLevel"] = m_sliderAlienNumberInLevel->value();
  root["AlienNumberOfLevels"] = m_sliderAlienNumberOfLevels->value();
  root["BulletHP"] = m_sliderBulletHP->value();
  root["BulletSpeed"] = m_sliderBulletSpeed->value();
  root["BulletDamage"] = m_sliderBulletDamage->value();
  root["BulletHP"] = m_sliderBulletHP->value();
  root["BulletSpeed"] = m_sliderBulletSpeed->value();
  root["BulletDamage"] = m_sliderBulletDamage->value();
  root["ObstacleHP"] = m_sliderObstacleHP->value();
  root["ObstacleNumberInGroup"] = m_sliderObstacleNumberInGroup->value();
  root["ObstacleNumberOfGroups"] = m_sliderObstacleNumberOfGroups->value();
  root["bulletsCount"] = 200;
  root["entities"]["gun"]["health"] = 50;
  root["entities"]["alien"]["health"] = 20;
  root["entities"]["obstacle"]["health"] = 15;
  std::ofstream settingsFile;
  settingsFile.open("settings.json");
  if (settingsFile.is_open())
  {
    Json::StyledWriter styledWriter;
    settingsFile << styledWriter.write(settings);
    settingsFile.close();
  }
}

void MainWindow::ReadJson()
{
  Json::Value settings;
  std::ifstream file("settings.json");
  if (file.is_open())
  {
    file >> settings;
    file.close();
  }
  m_glw.setGunHP(settings["settings"]["GunHP"].asInt());
  m_glw.setGunFiringRate(settings["settings"]["GunFiringRate"].asInt());
  m_glw.setGunSpeed(settings["settings"]["GunSpeed"].asInt());
  m_glw.setGunNumberOfLives(settings["settings"]["GunNumberOfLives"].asInt());

  m_glw.setAlienHP(settings["settings"]["AlienHP"].asInt());
  m_glw.setAlienFiringRate(settings["settings"]["AlienFiringRate"].asInt());
  m_glw.setAlienSpeed(settings["settings"]["AlienSpeed"].asInt());
  m_glw.setAlienNumberInLevel(settings["settings"]["AlienNumberInLevel"].asInt());
  m_glw.setAlienNumberOfLevels(settings["settings"]["AlienNumberOfLevels"].asInt());

  m_glw.setBulletHP(settings["settings"]["BulletHP"].asInt());
  m_glw.setBulletSpeed(settings["settings"]["BulletSpeed"].asInt());
  m_glw.setBulletDamage(settings["settings"]["BulletDamage"].asInt());

  m_glw.setObstacleHP(settings["settings"]["ObstacleHP"].asInt());
  m_glw.setObstacleNumberInGroup(settings["settings"]["ObstacleNumberInGroup"].asInt());
  m_glw.setObstacleNumberOfGroups(settings["settings"]["ObstacleNumberOfGroups"].asInt());

  /*
  std::cout << settings["settings"]["aliensCount"].asInt() << std::endl;
  std::cout << settings["settings"]["GunHP"].asInt() << std::endl;
  std::cout << settings["settings"]["GunFiringRate"].asInt() << std::endl;
  std::cout << settings["settings"]["GunSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["GunNumberOfLives"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienHP"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienFiringRate"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienNumberInLevel"].asInt() << std::endl;
  std::cout << settings["settings"]["AlienNumberOfLevels"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletHP"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletDamage"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletHP"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletSpeed"].asInt() << std::endl;
  std::cout << settings["settings"]["BulletDamage"].asInt() << std::endl;
  std::cout << settings["settings"]["ObstacleHP"].asInt() << std::endl;
  std::cout << settings["settings"]["ObstacleNumberInGroup"].asInt() << std::endl;
  std::cout << settings["settings"]["bulletsCount"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["gun"]["health"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["alien"]["health"].asInt() << std::endl;
  std::cout << settings["settings"]["entities"]["obstacle"]["health"].asInt() << std::endl;
  */
}


void MainWindow::StartGame()
{
  setCentralWidget(m_widgetInfo);
  //std::string lives = "Lives: " + m_sliderGunHP->value();
  //QString qlives(lives.c_str());
  //m_labelGameLives->setText(qlives);
}


void MainWindow::ConfigShow()
{
  setCentralWidget(m_centralWidget);
}

void MainWindow::Ready()
{
  this->hide();
  ReadJson();
/*
  m_glw.setGunHP(getGunHP());
  m_glw.setGunFiringRate(getGunFiringRate());
  m_glw.setGunSpeed(getGunSpeed());
  m_glw.setGunNumberOfLives(1);//getGunNumberOfLives());

  m_glw.setAlienHP(getAlienHP());
  m_glw.setAlienFiringRate(getAlienFiringRate());
  m_glw.setAlienSpeed(1);//getAlienSpeed());
  m_glw.setAlienNumberInLevel(getAlienNumberInLevel());
  m_glw.setAlienNumberOfLevels(getAlienNumberOfLevels());

  m_glw.setBulletHP(getBulletHP());
  m_glw.setBulletSpeed(getBulletSpeed());
  m_glw.setBulletDamage(1);//getBulletDamage());

  m_glw.setObstacleHP(getObstacleHP());
  m_glw.setObstacleNumberInGroup(getObstacleNumberInGroup());
  m_glw.setObstacleNumberOfGroups(getObstacleNumberOfGroups());
*/
  m_glw.show();
}

void MainWindow::GameOver()
{
  setCentralWidget(m_widgetGameOver);
}

int MainWindow::getGunHP()
{
  return m_sliderGunHP->value();
}

int MainWindow::getGunFiringRate()
{
  return m_sliderGunFiringRate->value();
}

int MainWindow::getGunSpeed()
{
  return m_sliderGunSpeed->value();
}

int MainWindow::getGunNumberOfLives()
{
  return m_sliderGunNumberOfLives->value();
}

int MainWindow::getAlienHP()
{
  return m_sliderAlienHP->value();
}

int MainWindow::getAlienFiringRate()
{
  return m_sliderAlienFiringRate->value();
}

int MainWindow::getAlienSpeed()
{
  return m_sliderAlienSpeed->value();
}

int MainWindow::getAlienNumberInLevel()
{
  return m_sliderAlienNumberInLevel->value();
}

int MainWindow::getAlienNumberOfLevels()
{
  return m_sliderAlienNumberOfLevels->value();
}


int MainWindow::getBulletHP()
{
  return m_sliderBulletHP->value();
}

int MainWindow::getBulletSpeed()
{
  return m_sliderBulletSpeed->value();
}

int MainWindow::getBulletDamage()
{
  return m_sliderBulletDamage->value();
}


int MainWindow::getObstacleHP()
{
  return m_sliderObstacleHP->value();
}

int MainWindow::getObstacleNumberInGroup()
{
  return m_sliderObstacleNumberInGroup->value();
}

int MainWindow::getObstacleNumberOfGroups()
{
  return m_sliderObstacleNumberOfGroups->value();
}

void MainWindow::ShowInfo()
{
  setCentralWidget(m_widgetInfo);
  this->show();
}

int MainWindow::getTotalScore()
{
  return m_totalScore;
}

int MainWindow::getLevel()
{
  return m_level;
}

void MainWindow::setTotalScore(int const n)
{
  m_totalScore = n;
}

void MainWindow::SetLevel(int const n)
{
  m_level = n;
}

void MainWindow::ChangeLevel(int const n)
{
  std::string level = "Level: " + n;
  QString qlevel(level.c_str());
  m_labelGameLevel->setText(qlevel);
}

void MainWindow::ChangeScore(int const n)
{
  std::string score = "Score: " + n;
  QString qscore(score.c_str());
  m_labelGameScore->setText(qscore);
}

void MainWindow::ChangeLives()
{

  std::string lives = "Lives: " + m_sliderGunHP->value();
  QString qlives(lives.c_str());
  m_labelGameLives->setText(qlives);
}

MainWindow::~MainWindow()
{

}
