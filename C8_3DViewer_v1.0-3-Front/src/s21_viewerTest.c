#include <check.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "./Back/s21_parse.h"
#include "./Back/s21_transform.h"

START_TEST(init_data_1) {
  data_z *data;

  data = init_data();
  ck_assert_ptr_nonnull(data);

  free(data);
}
END_TEST

START_TEST(parser_1) {
  char *filename = "data_null_test";
  data_z *data = NULL;
  ck_assert_int_eq(parser(filename, data), 0);
}
END_TEST

START_TEST(parser_2) {
  char *filename = "file_not_found";
  data_z *data = NULL;
  data = init_data();
  ck_assert_int_eq(parser(filename, data), 0);
  ck_assert_ptr_nonnull(data);
  free(data);
}
END_TEST

START_TEST(parser_3) {
  char *filename = "cube_first.obj";
  data_z *data = NULL;
  data = init_data();
  ck_assert_int_eq(parser(filename, data), 0);
  ck_assert_ptr_nonnull(data);
  free(data);
}
END_TEST

START_TEST(set_data_1) {
  data_z *data = NULL;
  ck_assert_int_eq(set_data(data), 1);
}
END_TEST

START_TEST(set_data_2) {
  data_z *data = NULL;

  int v, f;
  v = 4;
  f = 4;

  data = init_data();
  data->number_of_faces = f;
  data->number_of_vertexes = v;
  set_data(data);

  ck_assert_ptr_nonnull(data->matrix_3d.matrix);
  for (int i = 0; i < data->matrix_3d.rows; ++i)
    ck_assert_ptr_nonnull(data->matrix_3d.matrix[i]);
  ck_assert_ptr_nonnull(data->polygon);

  for (int i = 0; i < data->matrix_3d.rows; ++i)
    free(data->matrix_3d.matrix[i]);

  free(data->matrix_3d.matrix);
  free(data->polygon[0].vertexes);
  free(data->polygon);
  free(data);
}
END_TEST

START_TEST(polygon_conv_1) {
  data_z *data = NULL;
  ck_assert_int_eq(polygon_conv(data, "data_null_test", 0), 1);
}
END_TEST

START_TEST(polygon_conv_2) {
  data_z *data = malloc(sizeof(data_z));
  ck_assert_int_eq(polygon_conv(data, NULL, 0), 1);
  free(data);
}
END_TEST

START_TEST(polygon_conv_3) {
  data_z *data = NULL;
  int f, v, index;
  char *line;

  v = 4;
  f = 4;
  index = 1;
  line = "f 1 2 3";

  data = init_data();
  data->number_of_faces = f;
  data->number_of_vertexes = v;

  set_data(data);
  polygon_conv(data, line, index);

  ck_assert_ptr_nonnull(data->polygon[index].vertexes);
  for (int i = 0; i < data->polygon[index].verInFace_num; ++i)
    ck_assert_int_eq(data->polygon[index].vertexes[i], i + 1);

  free(data->polygon[index].vertexes);
  free(data->polygon[0].vertexes);
  free(data->polygon);
  for (int i = 0; i < data->matrix_3d.rows; ++i) {
    free(data->matrix_3d.matrix[i]);
  }
  free(data->matrix_3d.matrix);
}
END_TEST

START_TEST(move_x_1) {
  double arg;
  arg = 1.0;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 1; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = i;
    matrix_3d.matrix[i][1] = i;
    matrix_3d.matrix[i][2] = i;
  }
  x_move(&matrix_3d, arg);

  for (int i = 1; i < matrix_3d.rows; ++i)
    ck_assert_double_eq(matrix_3d.matrix[i][0], i + arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(move_y_1) {
  double arg;
  arg = 1.0;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 1; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = i;
    matrix_3d.matrix[i][1] = i;
    matrix_3d.matrix[i][2] = i;
  }
  y_move(&matrix_3d, arg);

  for (int i = 1; i < matrix_3d.rows; ++i)
    ck_assert_double_eq(matrix_3d.matrix[i][1], i + arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(move_z_1) {
  double arg;
  arg = 1.0;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 1; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = i;
    matrix_3d.matrix[i][1] = i;
    matrix_3d.matrix[i][2] = i;
  }
  z_move(&matrix_3d, arg);

  for (int i = 1; i < matrix_3d.rows; ++i)
    ck_assert_double_eq(matrix_3d.matrix[i][2], i + arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(ox_rotation_1) {
  double arg;
  arg = M_PI / 2;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 0; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = 1;
    matrix_3d.matrix[i][1] = 1;
    matrix_3d.matrix[i][2] = 1;
  }

  ox_rotation(&matrix_3d, arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    ck_assert_double_eq(matrix_3d.matrix[i][0], 1);
    ck_assert_double_eq(matrix_3d.matrix[i][1], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix_3d.matrix[i][2], -sin(arg) + cos(arg));
  }

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(oy_rotation_1) {
  double arg;
  arg = M_PI / 2;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 0; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = 1;
    matrix_3d.matrix[i][1] = 1;
    matrix_3d.matrix[i][2] = 1;
  }

  oy_rotation(&matrix_3d, arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    ck_assert_double_eq(matrix_3d.matrix[i][0], 1);
    ck_assert_double_eq(matrix_3d.matrix[i][1], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix_3d.matrix[i][2], -sin(arg) + cos(arg));
  }

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(oz_rotation_1) {
  double arg;
  arg = M_PI / 2;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 0; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = 1;
    matrix_3d.matrix[i][1] = 1;
    matrix_3d.matrix[i][2] = 1;
  }

  oz_rotation(&matrix_3d, arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    ck_assert_double_eq(matrix_3d.matrix[i][0], 1);
    ck_assert_double_eq(matrix_3d.matrix[i][1], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix_3d.matrix[i][2], -sin(arg) + cos(arg));
  }

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

START_TEST(scale_1) {
  double arg;
  arg = 1.1111;
  matrix_s matrix_3d;
  matrix_3d.rows = 2;
  matrix_3d.cols = 3;
  matrix_3d.matrix = (double **)malloc(sizeof(double *) * matrix_3d.rows);

  for (int i = 0; i < matrix_3d.rows; ++i)
    matrix_3d.matrix[i] = (double *)malloc(sizeof(double) * matrix_3d.cols);

  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix_3d.matrix[i][j] = .0;

  for (int i = 0; i < matrix_3d.rows; ++i) {
    matrix_3d.matrix[i][0] = 1;
    matrix_3d.matrix[i][1] = 1;
    matrix_3d.matrix[i][2] = 1;
  }
  scale(&matrix_3d, arg);
  for (int i = 0; i < matrix_3d.rows; ++i)
    for (int j = 0; j < matrix_3d.cols; ++j)
      ck_assert_double_eq(matrix_3d.matrix[i][j], arg);

  for (int i = 0; i < matrix_3d.rows; ++i) {
    free(matrix_3d.matrix[i]);
  }
  free(matrix_3d.matrix);
}
END_TEST

Suite *s21_3d() {
  Suite *suite;

  suite = suite_create("s21_3d");
  TCase *tcase_init_data = tcase_create("init_data");
  TCase *tcase_parser = tcase_create("parser");
  TCase *tcase_set_data = tcase_create("set_data");
  TCase *tcase_polygon_conv = tcase_create("polygon_conv");
  TCase *tcase_move = tcase_create("move");
  TCase *tcase_rotation = tcase_create("rotation");
  TCase *tcase_scale = tcase_create("tcase_scale");

  suite_add_tcase(suite, tcase_init_data);
  tcase_add_test(tcase_init_data, init_data_1);

  suite_add_tcase(suite, tcase_parser);
  tcase_add_test(tcase_parser, parser_1);
  tcase_add_test(tcase_parser, parser_2);
  tcase_add_test(tcase_parser, parser_3);

  suite_add_tcase(suite, tcase_set_data);
  tcase_add_test(tcase_set_data, set_data_1);
  tcase_add_test(tcase_set_data, set_data_2);

  suite_add_tcase(suite, tcase_polygon_conv);
  tcase_add_test(tcase_polygon_conv, polygon_conv_1);
  tcase_add_test(tcase_polygon_conv, polygon_conv_2);
  tcase_add_test(tcase_polygon_conv, polygon_conv_3);

  suite_add_tcase(suite, tcase_move);
  tcase_add_test(tcase_move, move_x_1);
  tcase_add_test(tcase_move, move_y_1);
  tcase_add_test(tcase_move, move_z_1);

  suite_add_tcase(suite, tcase_rotation);
  tcase_add_test(tcase_rotation, ox_rotation_1);
  tcase_add_test(tcase_rotation, oy_rotation_1);
  tcase_add_test(tcase_rotation, oz_rotation_1);

  suite_add_tcase(suite, tcase_scale);
  tcase_add_test(tcase_scale, scale_1);

  return suite;
}

int main() {
  Suite *suite = s21_3d();
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_VERBOSE);
  srunner_free(suite_runner);
  return 0;
}