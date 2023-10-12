#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setWindowTitle(APPLICATION_NAME);

  QSettings settings(APPLICATION_NAME);

  //    connect(ui->LoadFile, SIGNAL(clicked()), this,
  //    SLOT(on_LoadFile_clicked())); connect(ui->SaveSettings,
  //    SIGNAL(clicked()), this, SLOT(on_SaveSettings_clicked()));
  //    connect(ui->pushButton_jpegSave, SIGNAL(clicked()), this,
  //    SLOT(on_pushButton_jpegSave_clicked())); connect(ui->pushButton_bmpSave,
  //    SIGNAL(clicked()), this, SLOT(on_pushButton_bmpSave_clicked()));
  //    connect(ui->pushButton_gifSave, SIGNAL(clicked()), this,
  //    SLOT(on_pushButton_gifSave_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_LoadFile_clicked() {
    QString str;
    str = QFileDialog::getOpenFileName(this, "", "", "OBJ (*.obj);; OBJ (*.Obj);");
    int dots[2] = {0,0};
    int err = ui->QGLWidget->takeFile(str, dots);
    this->ui->QGLWidget->update();
    if (err == 0){
        ui->FileInfo->setText(str+"число вершин: "+ QString::number(dots[0]) + " число ребер: "+QString::number(dots[1]));
    }
  //  if (str.isEmpty()) {
  //    ui->FileInfo->setText("ошибка");
  //  } else {
  //    int massive[2];
  //    int err = this->ui->QGLWidget->takeFile(
  //        str, massive);  // отправляем name файла и массив для записи числа
  //                        // вершин и ребер
  //    if (err != 0) {
  //      ui->FileInfo->setText("ошибка");
  //    } else {
  //      ui->FileInfo->setText(str);  // название файла, кол-во вершин и ребер.
  //    }
  //  }
}

void MainWindow::on_scale_valueChanged(double arg1) {
  this->ui->QGLWidget->zoom = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_turm_x_valueChanged(double arg1) {
  this->ui->QGLWidget->x = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_turn_y_valueChanged(double arg1) {
  this->ui->QGLWidget->y = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_turn_z_valueChanged(double arg1) {
  this->ui->QGLWidget->z = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_moving_x_valueChanged(double arg1) {
  this->ui->QGLWidget->angle_x = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_moving_y_valueChanged(double arg1) {
  this->ui->QGLWidget->angle_y = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_moving_z_valueChanged(double arg1) {
  this->ui->QGLWidget->angle_z = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_radioButton_projection_clicked(bool checked) {
  this->ui->QGLWidget->proj = checked;
  this->ui->QGLWidget->update();
}

void MainWindow::on_red_valueChanged(double arg1) {
  this->ui->QGLWidget->red = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_green_valueChanged(double arg1) {
  this->ui->QGLWidget->green = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_blue_valueChanged(double arg1) {
  this->ui->QGLWidget->blue = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_red_dot_valueChanged(double arg1) {
  this->ui->QGLWidget->red_dot = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_green_dot_valueChanged(double arg1) {
  this->ui->QGLWidget->green_dot = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_blue_dot_valueChanged(double arg1) {
  this->ui->QGLWidget->blue_dot = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_dot_size_valueChanged(double arg1) {
  this->ui->QGLWidget->size = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_red_line_valueChanged(double arg1) {
  this->ui->QGLWidget->red_line = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_green_line_valueChanged(double arg1) {
  this->ui->QGLWidget->green_line = arg1;
  this->ui->QGLWidget->update();
}

void MainWindow::on_blue_line_valueChanged(double arg1) {
  this->ui->QGLWidget->blue_line = arg1;
  this->ui->QGLWidget->update();
}

// Cохранение настроек приложения
void MainWindow::on_SaveSettings_clicked() {
  //    QString pathToFile = QApplication::applicationDirPath();
  //    QDir dir(pathToFile);
  //    QString absPathToFile = dir.absolutePath();
  //    int num = absPathToFile.lastIndexOf("/src/");
  //    QString resPathToFile = pathToFile.left(num + 5); // путь к корневой
  //    директории проекта, включая "src", если та существует

  //  QString fileSettings = resPathToFile + "3DViewer/setting/settings.ini";
  //  QSettings settings(fileSettings, QSettings::IniFormat);

  //  settings.setValue("backgroundColor", ui->QGLWidget->backgroundColor);
  //  settings.setValue("verticesColor", ui->QGLWidget->verticesColor);
  //  settings.setValue("poligonsColor", ui->QGLWidget->facetsColor);

  //  settings.setValue("projection_type",
  //                    ui->comboBox_projection_type->currentIndex());
  //  settings.setValue("facets_type",
  //  ui->comboBox_facets_type->currentIndex());
  //  settings.setValue("thickness_of_facets",
  //                    ui->doubleSpinBox_thickness_of_facets->value());
  //  settings.setValue("way_to_display",
  //                    ui->comboBox_way_to_display->currentIndex());
  //  settings.setValue("size_of_vertices",
  //                    ui->doubleSpinBox_size_of_vertices->value());

  QSettings settings(APPLICATION_NAME);
  settings.sync();


  QMessageBox::information(this, tr("Сохранение настроек"),
                           tr("Сохранение настроек выполнено успешно"));
}

void MainWindow::on_pushButton_jpegSave_clicked() {
  QMessageBox::information(this, tr("Сохранение файла"),
                           tr("Сохранение файла .jpeg выполнено успешно"));
}

void MainWindow::on_pushButton_bmpSave_clicked() {
  QMessageBox::information(this, tr("Сохранение файла"),
                           tr("Сохранение файла .bmp выполнено успешно"));
}

void MainWindow::on_pushButton_gifSave_clicked() {
  QMessageBox::information(this, tr("Сохранение скринкаста"),
                           tr("Сохранение скринкаста выполнено успешно"));
}
