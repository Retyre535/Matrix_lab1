#ifndef TESTS_H
#define TESTS_H
#include <stdbool.h>
#include "Matrix.h"

void create_int_matrices();
void create_result_int_matrices_transposition();
bool matrix_equality_check(Matrix* matrix1, Matrix* matrix2);
void transposition_int_tests();

#endif //TESTS_H
