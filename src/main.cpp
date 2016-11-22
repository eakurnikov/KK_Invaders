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

#include "gl_widget.hpp"
#include "mainwindow.hpp"
#include <QApplication>
#include <QColor>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  GLWidget glw(&w, QColor(255,1,1,1));
  //w.show();
  glw.show();

  return a.exec();
}
