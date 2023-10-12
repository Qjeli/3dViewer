#ifndef S21_PARSE_H_
#define S21_PARSE_H_
#define _GNU_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct of faces
typedef struct porygon {  // края
  int *vertexes;          // вершина
  int verInFace_num;      // number of vertexes in faces
} porygon_z;              // funny pokemon name)

// Struct of matrix
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int cols;
} matrix_s;

typedef struct data {
  int number_of_vertexes;
  int number_of_faces;
  int overrall_dot_number;
  int overrall_line_number;
  porygon_z *polygon;
  matrix_s matrix_3d;
} data_z;

data_z *init_data();
int parser(char *filename, data_z *data);
int set_data(data_z *data);
int polygon_conv(data_z *data, char *line, int index);

#endif  // SRC_S21_PARSE_H_