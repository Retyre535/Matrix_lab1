#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"
#include <math.h>

void init_matrix(Matrix* matrix, size_t rows, size_t cols) {
    matrix->elements = malloc(rows*cols * sizeof(Element));
    matrix->rows = rows;
    matrix->cols = cols;
}

void add_element(Matrix* matrix, size_t row, size_t col, void* data, Data_type type) {
    size_t index = row * matrix->cols + col;
    matrix->elements[index].data = data;
    matrix->elements[index].type = type;
}

Matrix matrices_sum(Matrix* matrix1, Matrix* matrix2) {
    Matrix result;
    init_matrix(&result, matrix1->rows, matrix1->cols);
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Matrices size is different");
    } else {
        for (size_t i = 0; i < matrix1->rows; i++) {
            for (size_t j = 0; j < matrix1->cols; j++) {
                size_t index = i * matrix1->cols + j;
                result.elements[index].type = matrix1->elements[index].type;
                if (matrix1->elements[index].type == INT && matrix2->elements[index].type == INT) {
                    int* a = (int*)matrix1->elements[index].data;
                    int* b = (int*)matrix2->elements[index].data;
                    int* sum = malloc(sizeof(int));
                    *sum = *a + *b;
                    result.elements[index].data = sum;
                } else if (matrix1->elements[i].type == FLOAT && matrix2->elements[i].type == FLOAT) {
                    float* a = (float*)matrix1->elements[index].data;
                    float* b = (float*)matrix2->elements[index].data;
                    float* sum = malloc(sizeof(float));
                    *sum = *a + *b;
                    result.elements[index].data = sum;
                } else {
                    printf("Different matrices elements types");
                }
            }
        }
    }
    return result;
}

Matrix transposition_matrix(Matrix* matrix) {
    Matrix result;
    init_matrix(&result, matrix->cols, matrix->rows);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            size_t old_index = i * matrix->cols + j;
            size_t new_index = j * matrix->rows + i;
            result.elements[new_index].type = matrix->elements[old_index].type;
            if (matrix->elements[old_index].type == INT) {
                int* a = (int*)matrix->elements[old_index].data;
                int* b = malloc(sizeof(int));
                *b = *a;
                result.elements[new_index].data = b;
            }
            else if (matrix->elements[old_index].type == FLOAT) {
                float* a = (float*)matrix->elements[old_index].data;
                float* b = malloc(sizeof(float));
                *b = *a;
                result.elements[new_index].data = b;
            }
        }
    }
    return result;
}

void matrix_output(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            size_t index = i * matrix->cols + j;
            if (matrix->elements[index].type == INT) {
                printf("%d ", *(int*)matrix->elements[index].data);
            } else if (matrix->elements[index].type == FLOAT) {
                printf("%.2f ", *(float*)matrix->elements[index].data);
            }
        }
        printf("\n");
    }
}

void free_matrix(Matrix* matrix) {
    for (size_t i = 0; i<matrix->rows*matrix->cols; i++) {
        free(matrix->elements[i].data);
    }
    free(matrix->elements);
}

Matrix matrix_multiplication(Matrix* matrix1, Matrix* matrix2) {
    Matrix result;
    init_matrix(&result, matrix1->rows, matrix2->cols);
    if (matrix1->cols != matrix2->rows) {
        printf("Multiplication is not possible due to the matrix sizes.");
    } else {
        for (size_t i = 0; i < matrix1->rows; i++) {
            for (size_t j = 0; j < matrix2->cols; j++) {
                size_t index = i * matrix2->cols + j;
                result.elements[index].type = matrix1->elements[0].type;
                if (matrix1->elements[0].type == INT) {
                    int* sum = malloc(sizeof(int));
                    *sum = 0;
                    for (size_t k = 0; k < matrix1->cols; k++) {
                        int* a = (int*)matrix1->elements[i * matrix1->cols + k].data;
                        int* b = (int*)matrix2->elements[k * matrix2->cols + j].data;
                        *sum += (*a) * (*b);
                    }
                    result.elements[index].data = sum;
                }else if (matrix1->elements[index].type == FLOAT) {
                    float* sum = malloc(sizeof(float));
                    *sum = 0.0f;
                    for (size_t k = 0; k < matrix1->cols; k++) {
                        float* a = (float*)matrix1->elements[i * matrix1->cols + k].data;
                        float* b = (float*)matrix2->elements[k * matrix2->cols + j].data;
                        *sum += (*a) * (*b);
                    }
                    result.elements[index].data = sum;
                }
            }
        }
    }
    return result;
}

void matrix_input(Matrix* matrix, Data_type type) {
    printf("\nEnter the number of rows: ");
    scanf("%zu", &matrix->rows);
    printf("Enter the number of cols: ");
    scanf("%zu", &matrix->cols);
    init_matrix(matrix, matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            printf("Enter the matrix element [%zu][%zu]: ", i, j);
            if (type == INT) {
                int* new_element = malloc(sizeof(int));
                scanf("%d", new_element);
                add_element(matrix, i, j, new_element, INT);
            } else if (type == FLOAT) {
                float* new_element = malloc(sizeof(float));
                scanf("%f", new_element);
                add_element(matrix, i, j, new_element, FLOAT);
            }
        }
    }
    matrix_output(matrix);
}

Matrix add_linear_combination_to_row(Matrix* matrix, size_t row_target, size_t row_source, float factor) {
    Matrix result, matrix2;
    init_matrix(&result, matrix->rows, matrix->cols);
    init_matrix(&matrix2, matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            size_t index = i * matrix->cols + j;
            result.elements[index].type = matrix->elements[index].type;
            matrix2.elements[index].type = matrix->elements[index].type;
            if (i == row_target) {
                if (matrix->elements[index].type == INT) {
                    int* a = malloc(sizeof(int));
                    *a = *(int*)matrix->elements[row_source*matrix->cols+j].data*factor;
                    matrix2.elements[index].data = a;
                } else if (matrix->elements[index].type == FLOAT) {
                    float* a = malloc(sizeof(float));
                    *a = *(float*)matrix->elements[row_source*matrix->cols+j].data*factor;
                    matrix2.elements[index].data = a;
                }
            }else {
                if (matrix->elements[index].type == INT) {
                    int* a = malloc(sizeof(int));
                    *a = *(int*)matrix->elements[index].data*0;
                    matrix2.elements[index].data = a;
                } else if (matrix->elements[index].type == FLOAT) {
                    float* a = malloc(sizeof(float));
                    *a = *(float*)matrix->elements[index].data*0;
                    matrix2.elements[index].data = a;
                }
            }
        }
    }
    result = matrices_sum(matrix, &matrix2);
    return result;
}