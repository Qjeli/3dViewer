#include "glwidget.h"
//#include <GL/glut.h> // для линукса
#include <OpenGL/glu.h> // для мака
GLWidget::GLWidget(QWidget *parent)  : QOpenGLWidget(parent), size(5), angle(0) //tranponse
{
    this->setFocusPolicy( Qt::StrongFocus );

}

//GLWidget:: data_s figure_info;
 data_z data = {0};

void GLWidget::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST); // буфф глубины
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );  // рисуем без заливки
    // load sheaders
    initShaders();
}


void GLWidget::paintGL() // перерисовка содержимого окна
{
    glClearColor(red/255.0f,green/255.0f,blue/255.0f, alpha/255.0f);
    qDebug()<< red;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // очищаем содержимое Это буффер цвета и глубины
    //changeView(proj);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Выставляем цвет рисования
//    x_move(figure_info.matrix_in_3d, x);
//    y_move(figure_info.matrix_in_3d, y);
//    z_move(figure_info.matrix_in_3d, z);

//    ox_rotation(figure_info.matrix_in_3d,  angle_x);
//    oy_rotation(figure_info.matrix_in_3d,  angle_y);
//    oz_rotation(figure_info.matrix_in_3d,  angle_z);

//    scale(figure_info.matrix_in_3d, zoom);


//    glDrawArrays(GL_POINTS, 0, figure_info.number_of_faces); // последним параметром надо получить сколько всего точек

//    glEnableClientState(GL_VERTEX_ARRAY);

    //Test_drow();
    if(data.number_of_vertexes > 0){
    our_function_to_drow();
    }
//    glDisableClientState(GL_VERTEX_ARRAY);
//    glutSolidSphere(1,20,20);
}

void GLWidget::our_function_to_drow(){

    glPointSize( size );
    x_move(&data.matrix_3d, x);
    y_move(&data.matrix_3d, y);
    z_move(&data.matrix_3d, z);
    ox_rotation(&data.matrix_3d, angle_x);
    oy_rotation(&data.matrix_3d, angle_y);
    oz_rotation(&data.matrix_3d, angle_z);
    scale(&data.matrix_3d, zoom);
    double arr[data.matrix_3d.cols* data.matrix_3d.rows];
    int f = 0;
    for(int i = 0; i < data.matrix_3d.cols; i++){
        for(int j = 0; j < data.matrix_3d.rows; j++){
            arr[f] = data.matrix_3d.matrix[i][j];
                    f++;
        }
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, arr);


     glColor3f( 255, 0.0f, 0.0f ); // цвет точек и потом рисуем отдельно линии
     glDrawArrays(GL_POINTS, 0, data.overrall_dot_number);

    int arr2[6*data.overrall_line_number];
    f = 0;
    for(int i = 0; i < data.overrall_line_number; i++){
        for(int j = 0; j < 6; j++){
            arr[f] = data.polygon[i].vertexes[j];
                    f++;
        }
    }

////    glDrawArrays(GL_POINTS, 0, data.matrix_3d);

    glColor3f( red_line/255.0f, green_line/0.0f, blue_line/0.0f ); // цвет линий
    glDrawElements(GL_LINES, data.number_of_vertexes, GL_UNSIGNED_INT, arr2);

    glDisableClientState(GL_VERTEX_ARRAY);

}


void GLWidget::Test_drow(){
        glPushMatrix();
    { // для независимого поворота
        glPointSize( size ); // размер точек
        qDebug() << angle;
        glScalef(zoom, zoom, zoom);

        glRotatef( angle_z, 0, 0, 1 ); // поворот: угол поворота и координаты конца отрезка (или лучше сказать - вектора),
        glRotatef( angle_y, 0, 1, 0 );
        glRotatef( angle_x, 1, 0, 0 );
        // вокруг которого будет осуществлён поворот. Начало отрезка имеет координаты: (0, 0, 0).
        glColor3f( red_dot/0.0f, green_dot/240.0f, blue_dot/0.0f );

       // Рисуем точки
       glBegin( GL_POINTS );
       {
           glVertex3f( -10, 10, 10);
           glVertex3f( 10, 10, 10);
           glVertex3f( 10, -10, -10);
           glVertex3f( -10, -10, -10);
       }
       glEnd();
       glColor3f( red_line/255.0f, green_line/0.0f, blue_line/0.0f );
           // Рисуем квадратик
           glBegin( GL_QUADS );
           {
               glVertex2f( -150, 50 );
               glVertex2f( -50, 50 );
               glVertex2f( -50, -50 );
               glVertex2f( -150, -50 );
           }
           glEnd();

           // Второй квадратик
           // Выставляем цвет рисования
           glColor3f( red_line/0.0f, green_line/50.0f, blue_line/230.0f );
           // Рисуем квадратик
           glBegin( GL_QUADS );
           {
               glVertex2f( 50, 50 );
               glVertex2f( 150, 50 );
               glVertex2f( 150, -50 );
               glVertex2f( 50, -50 );
           }
           glEnd();
    }
       glPopMatrix();
}


void GLWidget::resizeGL(int w, int h) // при изменении размера
{
//    glViewport(0, 0, w, h);
    glViewport( 0, 0, w, h );

       // Reset coordinate system
       glMatrixMode( GL_PROJECTION );
       glLoadIdentity();

       // Establish clipping volume (left, right, bottom, top, near, far)
       glOrtho( -5, 5, -5, 5, -5, 5 );

       glMatrixMode( GL_MODELVIEW );
       glLoadIdentity();
}

//GLWidget::data_z data;

void GLWidget::connect(QString str)
{

    qDebug() << str;
    QByteArray ba = str.toLocal8Bit();
    char *c_str2 = ba.data();
    int err = parser(c_str2, &data);

}



int GLWidget::takeFile(QString str, int *dots)
{
    qDebug() << str;
    QByteArray ba = str.toLocal8Bit();
    char *c_str2 = ba.data();
    int err = parser(c_str2, &data);
    dots[0]=data.number_of_vertexes;
    dots[1]=data.number_of_faces;
    return err;
//    figure_info = {'\0'}; // зануляем структуру
//    int err = parser(str, figure_info); // функция на си. передаем имя файла
//    if(err == 0)
//        update();
//    return err;
}




void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch( event->key() ) {
            case Qt::Key_Up:
                qDebug() << "Up";
                break;
            case Qt::Key_Right:
                qDebug() << "Right";
                angle += 10;
                break;
            case Qt::Key_Down:
                qDebug() << "Down";
                break;
            case Qt::Key_Left:
                qDebug() << "Left";
                angle -= 10;
            break;
        }
    angle = angle % 360;

    update();
}

void GLWidget::changeView(bool proj)
{

    glMatrixMode(GL_PROJECTION);  // ортоганальая поекция
      glLoadIdentity();             // загружаем матрицу
      if (proj) {
        // Establish clipping volume (left, right, bottom, top, near, far)
        glFrustum(-1, 1, -1, 1, 1, 99999);  //  перспективная проекция

      } else {
        glOrtho(-1, 1, -1, 1, -1, 99999);// отоганальная

      }
}

void GLWidget::initShaders()
{

}
