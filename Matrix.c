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
                    int* elements1 = (int*)matrix1->elements[index].data;
                    int* elements2 = (int*)matrix2->elements[index].data;
                    int* sum = malloc(sizeof(int));
                    *sum = *elements1 + *elements2;
                    result.elements[index].data = sum;
                } else if (matrix1->elements[i].type == FLOAT && matrix2->elements[i].type == FLOAT) {
                    float* elements1 = (float*)matrix1->elements[index].data;
                    float* elements2 = (float*)matrix2->elements[index].data;
                    float* sum = malloc(sizeof(float));
                    *sum = *elements1 + *elements2;
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
                int* elements_old = (int*)matrix->elements[old_index].data;
                int* elements_new = malloc(sizeof(int));
                *elements_new = *elements_old;
                result.elements[new_index].data = elements_new;
            }
            else if (matrix->elements[old_index].type == FLOAT) {
                float* elements_old = (float*)matrix->elements[old_index].data;
                float* elements_new = malloc(sizeof(float));
                *elements_new = *elements_old;
                result.elements[new_index].data = elements_new;
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
        printf("Multiplication impossible: %zux%zu and %zux%zu\n", matrix1->rows, matrix1->cols, matrix2->rows, matrix2->cols);
        free_matrix(&result);
        init_matrix(&result, 0, 0);
        return result;
    }
    Data_type result_type = matrix1->elements[0].type;
    if (result_type != matrix2->elements[0].type) {
        printf("Different types of matrices\n");
        free_matrix(&result);
        init_matrix(&result, 0, 0);
        return result;
    }
    for (size_t i = 0; i < matrix1->rows; i++) {
        for (size_t j = 0; j < matrix2->cols; j++) {
            size_t index = i * matrix2->cols + j;
            result.elements[index].type = result_type;
            if (result_type == INT) {
                int sum = 0;
                for (size_t k = 0; k < matrix1->cols; k++) {
                    int* val1 = (int*)matrix1->elements[i * matrix1->cols + k].data;
                    int* val2 = (int*)matrix2->elements[k * matrix2->cols + j].data;
                    sum += (*val1) * (*val2);
                }
                int* sum_ptr = malloc(sizeof(int));
                *sum_ptr = sum;
                result.elements[index].data = sum_ptr;
            }
            else { // FLOAT
                float sum = 0.0f;
                for (size_t k = 0; k < matrix1->cols; k++) {
                    float* val1 = (float*)matrix1->elements[i * matrix1->cols + k].data;
                    float* val2 = (float*)matrix2->elements[k * matrix2->cols + j].data;
                    sum += (*val1) * (*val2);
                }
                float* sum_ptr = malloc(sizeof(float));
                *sum_ptr = sum;
                result.elements[index].data = sum_ptr;
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
    Matrix result;
    init_matrix(&result, matrix->rows, matrix->cols);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            size_t index = i * matrix->cols + j;
            result.elements[index].type = matrix->elements[index].type;
            if (matrix->elements[index].type == INT) {
                int* element = malloc(sizeof(int));
                *element = *(int*)matrix->elements[index].data;
                result.elements[index].data = element;
            } else if (matrix->elements[index].type == FLOAT) {
                float* element = malloc(sizeof(float));
                *element = *(float*)matrix->elements[index].data;
                result.elements[index].data = element;
            }
        }
    }
    for (size_t j = 0; j < matrix->cols; j++) {
        size_t target_index = row_target * matrix->cols + j;
        size_t source_index = row_source * matrix->cols + j;
        if (matrix->elements[target_index].type == INT) {
            int* target_elements = (int*)result.elements[target_index].data;
            int* source_elements = (int*)matrix->elements[source_index].data;
            *target_elements += (int)(factor * (*source_elements));
        } else if (matrix->elements[target_index].type == FLOAT) {
            float* target_elements = (float*)result.elements[target_index].data;
            float* source_elements = (float*)matrix->elements[source_index].data;
            *target_elements += factor * (*source_elements);
        }
    }
    return result;
}