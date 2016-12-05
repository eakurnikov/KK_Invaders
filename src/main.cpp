#include <iostream>
#include "space.hpp"
#include "gameentity.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include "bullet.hpp"
#include "logger.hpp"
//#include "factory.hpp"
#include <vector>
#include <list>
#include <memory>
#include <string>

#include "gl_widget.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <QColor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  //GLWidget glw(&w, QColor(255,1,1,1));
  w.show();
  //glw.show();

  /*std::unique_ptr<Alien> al = Factory::Instance().Create<Alien>();
  std::unique_ptr<Gun> g = Factory::Instance().Create<Gun>();
  std::unique_ptr<Obstacle> ob = Factory::Instance().Create<Obstacle>();
  std::vector<std::unique_ptr<Bullet>> bullets ;
  bullets.push_back(Factory::Instance().Create<Bullet>(*g));
  bullets.push_back(Factory::Instance().Create<Bullet>(*al));
  g->Shot();
  bullets[0]->Hit(*ob);
  al->Shot();
  bullets[1]->Hit(*ob);*/
  return a.exec();
}
