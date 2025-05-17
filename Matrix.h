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
void matrix_output(Matrix* matrix);
void free_matrix(Matrix* matrix);

Matrix matrices_sum_int(Matrix* matrix1, Matrix* matrix2);
Matrix matrices_sum_float(Matrix* matrix1, Matrix* matrix2);
Matrix (*get_sum_function(Data_type type))(Matrix*, Matrix*);

Matrix transposition_matrix_int(Matrix* matrix);
Matrix transposition_matrix_float(Matrix* matrix);
Matrix (*get_transposition_function(Data_type type))(Matrix*);

Matrix matrix_multiplication_int(Matrix* matrix1, Matrix* matrix2);
Matrix matrix_multiplication_float(Matrix* matrix1, Matrix* matrix2);
Matrix (*get_multiplication_function(Data_type type))(Matrix*, Matrix*);

void matrix_input_int(Matrix* matrix);
void matrix_input_float(Matrix* matrix);
void (*get_input_function(Data_type type))(Matrix*);

Matrix add_linear_combination_to_row_int(Matrix* matrix, size_t row_target, size_t row_source, float factor);
Matrix add_linear_combination_to_row_float(Matrix* matrix, size_t row_target, size_t row_source, float factor);
Matrix (*get_linear_combination_function(Data_type type))(Matrix*, size_t, size_t, float);

#endif //MATRIX_H