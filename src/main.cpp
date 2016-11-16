#include <iostream>
#include "space.hpp"
#include "gameentity.hpp"
#include "point2d.hpp"
#include "box2d.hpp"
#include "ray2d.hpp"
#include "bullet.hpp"
#include "logger.hpp"
#include "factory.hpp"
#include <vector>
#include <list>
#include <memory>
#include <string>

#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
