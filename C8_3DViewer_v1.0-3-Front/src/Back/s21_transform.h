#ifndef S21_TRANSFORM_H_
#define S21_TRANSFORM_H_

#include "s21_parse.h"

//  Movement
void x_move(matrix_s *A, double a);
void y_move(matrix_s *A, double a);
void z_move(matrix_s *A, double a);

//  Rotation
void ox_rotation(matrix_s *A, double angle);
void oy_rotation(matrix_s *A, double angle);
void oz_rotation(matrix_s *A, double angle);

//  Scaling
void scale(matrix_s *A, double zoom);

#endif  // S21_TRANSFORM_H