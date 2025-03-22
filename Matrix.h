//
// Created by JDubo on 21.03.2025.
//
#ifndef MATRIX_H
#define MATRIX_H

#include <stddef.h>

typedef enum {
    INT,
    FLOAT
} Data_type;

typedef struct {
    void* data;
    Data_type type;
} Element;

typedef struct {
    Element* elements;
    size_t rows;
    size_t cols;
} Matrix;

void init_matrix(Matrix* matrix, size_t rows, size_t cols);
void add_element(Matrix* matrix, size_t row, size_t col, void* data, Data_type type);
Matrix matrices_sum(Matrix* matrix1, Matrix* matrix2);
Matrix transposition_matrix(Matrix* matrix);
void matrix_output(Matrix* matrix);
void free_matrix(Matrix* matrix);
Matrix matrix_multiplication(Matrix* matrix1, Matrix* matrix2);
void matrix_input(Matrix* matrix, Data_type type);
void add_linear_combination_to_row(Matrix* matrix, size_t row_target, size_t* col_source,
    float* factor, size_t new_row);

#endif //MATRIX_H
