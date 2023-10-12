#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

#include <QFileDialog>
#include <QObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

//#include <QGLWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>

extern "C" {
#include "../Back/s21_parse.h"
#include "../Back/s21_transform.h"
}

#define GL_SILENCE_DEPRECATION

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:

  explicit GLWidget(QWidget *parent = 0);
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;
  void connect(QString str);
  void SetAngle(int x);
  int takeFile(QString str, int *dots);
  void keyPressEvent(QKeyEvent *event) override;
   void Test_drow();
  //бонус
  void changeView(bool proj);
  // init cube
  void initShaders();
  double x, y, z;
  double angle_x, angle_y, angle_z;
  double zoom;
  bool proj;
  double red, green, blue, alpha;
  double red_dot, green_dot, blue_dot;
  double size;
  double red_line, green_line, blue_line;
  void our_function_to_drow();
  data_z data;


 private:
  int angle;
  QTimer timer;
  //    QOpenGLShaderProgram;
};

#endif  // GLWIDGET_H
