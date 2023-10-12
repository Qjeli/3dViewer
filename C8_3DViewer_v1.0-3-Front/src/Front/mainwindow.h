#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QOpenGLWidget>
#include <QSettings>
#include <QtOpenGL>

#define APPLICATION_NAME "3DViewer"

extern "C" {
#include "../Back/s21_parse.h"
#include "../Back/s21_transform.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_LoadFile_clicked();

  void on_scale_valueChanged(double arg1);

  void on_turm_x_valueChanged(double arg1);
  void on_turn_y_valueChanged(double arg1);
  void on_turn_z_valueChanged(double arg1);

  void on_moving_x_valueChanged(double arg1);
  void on_moving_y_valueChanged(double arg1);
  void on_moving_z_valueChanged(double arg1);

  void on_radioButton_projection_clicked(bool checked);

  void on_red_valueChanged(double arg1);
  void on_green_valueChanged(double arg1);
  void on_blue_valueChanged(double arg1);

  void on_red_dot_valueChanged(double arg1);
  void on_green_dot_valueChanged(double arg1);
  void on_blue_dot_valueChanged(double arg1);

  void on_dot_size_valueChanged(double arg1);

  void on_red_line_valueChanged(double arg1);
  void on_green_line_valueChanged(double arg1);
  void on_blue_line_valueChanged(double arg1);

  void on_SaveSettings_clicked();
  void on_pushButton_jpegSave_clicked();
  void on_pushButton_bmpSave_clicked();
  void on_pushButton_gifSave_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
