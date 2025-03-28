#ifndef TESTS_H
#define TESTS_H
#include <stdbool.h>
#include <stdio.h>
#include "Matrix.h"

typedef struct {
    Matrix* matrices;
    Matrix* transpositions;
    Matrix* sums;
    Matrix* multiplications;
    int* sum_indexes;
    int* multiplication_indexes;
    size_t matrix_count;
    size_t sum_count;
    size_t mul_count;
} Matrix_test_data;

bool matrix_equality_check(Matrix* matrix1, Matrix* matrix2);
void free_test_data(Matrix_test_data* data);
int read_matrix(FILE* file, Matrix* matrix, Data_type type);
int read_test_file(const char* filename, Matrix_test_data* data, Data_type type);
void run_file_tests(const char* filename, Data_type type);

#endif //TESTS_H
