#include <QApplication>

#include "mainwindow.h"
//#include <GL/glut.h>

int main(int argc, char *argv[]) {
  //    glutInit(&argc, argv);

  QCoreApplication::setApplicationName(APPLICATION_NAME);

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
