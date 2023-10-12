#include "s21_transform.h"

//  Translation
void x_move(matrix_s *A, double a) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] += a;
  }
}

void y_move(matrix_s *A, double a) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][1] += a;
  }
}

void z_move(matrix_s *A, double a) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][2] += a;
  }
}

//  Rotation
void ox_rotation(matrix_s *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_y = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_y + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_y + cos(angle) * temp_z;
  }
}

void oy_rotation(matrix_s *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_x + sin(angle) * temp_z;
    A->matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_z;
  }
}

void oz_rotation(matrix_s *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][1];
    double temp_y = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * temp_x + sin(angle) * temp_y;
    A->matrix[i][2] = -sin(angle) * temp_x + cos(angle) * temp_y;
  }
}

// Scaling
void scale(matrix_s *A, double zoom) {
  if (zoom != 0) {
    for (int i = 0; i < A->rows; i++) {
      A->matrix[i][0] *= zoom;
      A->matrix[i][1] *= zoom;
      A->matrix[i][2] *= zoom;
    }
  }
}