#include "s21_parse.h"

data_z *init_data() {
  data_z *data = NULL;
  data = (data_z *)malloc(sizeof(data_z));
  // Initializing polygons
  data->number_of_faces = 0;
  data->number_of_vertexes = 0;
  data->overrall_dot_number = 0;
  data->overrall_line_number = 0;
  data->polygon = NULL;
  // Initializing matrix
  data->matrix_3d.matrix = NULL;
  data->matrix_3d.rows = 0;
  data->matrix_3d.cols = 0;

  return data;
}

int parser(char *filename, data_z *data) {
  FILE *file;
  fpos_t pos;

  char *line;
  size_t len;

  len = 100;
  line = malloc(len);
  int err = 0;

  if (((file = fopen(filename, "r")) == NULL) || (data == NULL)) {  // if error
    return err;
  } else {
    fgetpos(file, &pos);
    while (getline(&line, &len, file) != -1) {
      if ('f' == line[0] && ' ' == line[1]) {
        data->number_of_faces += 1;
        data->overrall_dot_number += 1;
      }
      if ('v' == line[0] && ' ' == line[1]) {
        data->number_of_vertexes += 1;
        data->overrall_dot_number += 1;
      }
    }
    fsetpos(file, &pos);
    set_data(data);

    int v = 1, f = 1;  //  can't be 0
    while (getline(&line, &len, file) != -1) {
      if ('v' == line[0] && ' ' == line[1]) {
        if (sscanf(line, "v %lf%lf%lf", &data->matrix_3d.matrix[v][0],
                   &data->matrix_3d.matrix[v][1],
                   &data->matrix_3d.matrix[v][2]) != 0) {
          ++v;
          data->overrall_line_number += 1;
        }
      }
      if ('f' == line[0] && ' ' == line[1]) {
        polygon_conv(data, line, f);
        ++f;
        data->overrall_line_number += 1;
      }
    }
  }
  free(line);
  fclose(file);
  return err;
}

int set_data(data_z *data) {
  int err = 0;

  if (data == NULL) {
    err = 1;
  } else {
    data->matrix_3d.rows = data->number_of_vertexes + 1;
    data->matrix_3d.cols = 3;
    data->matrix_3d.matrix =
        (double **)malloc(sizeof(double *) * data->matrix_3d.rows);

    //  Populating matrix
    for (int i = 0; i < data->matrix_3d.rows; ++i) {
      data->matrix_3d.matrix[i] =
          (double *)malloc(sizeof(double) * data->matrix_3d.cols);
      for (int j = 0; j < data->matrix_3d.cols; ++j) {
        data->matrix_3d.matrix[i][j] = 0.0;  // Initialize the matrix elements
      }
    }
    data->polygon = malloc(sizeof(porygon_z) * (data->number_of_faces + 1));
    data->polygon[0].vertexes = malloc(1);
  }
  return err;
}

int polygon_conv(data_z *data, char *line, int index) {
  int err = 0;
  if (data == NULL || line == NULL) {
    err = 1;
  } else {
    int count = 0;
    char *tmp_line = NULL;
    tmp_line = malloc(strlen(line) + 1);
    char *tmp = NULL;
    int digit = 0;

    strcpy(tmp_line, line);
    tmp = strtok(tmp_line, " ");  // Read past the initial "f"

    for (; (tmp = strtok(NULL, " ")) != NULL && (atoi(tmp) != 0); ++count) {
      ;
    }

    data->polygon[index].verInFace_num = count;
    data->polygon[index].vertexes = malloc(sizeof(int) * count);
    
    strcpy(tmp_line, line);
    tmp = strtok(tmp_line, " ");
    tmp = strtok(NULL, " ");

    for (int i = 0; i < data->polygon[index].verInFace_num; ++i) {
      digit = atoi(tmp);
      if (digit != 0) {
        data->polygon[index].vertexes[i] = digit;
      }
      tmp = strtok(NULL, " ");
    }
    free(tmp_line);
  }
  return err;
}
