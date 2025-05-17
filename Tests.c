#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Matrix.h"
#include "Tests.h"
#define FLOAT_EPSILON 1e-5f

bool matrix_equality_check(Matrix* matrix1, Matrix* matrix2) {
    if (!matrix1 || !matrix2 || !matrix1->elements || !matrix2->elements) {
        return false;
    }
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        return false;
    }
    for (size_t i = 0; i < matrix1->rows; i++) {
        for (size_t j = 0; j < matrix1->cols; j++) {
            size_t index = i * matrix1->cols + j;
            Element* elements1 = &matrix1->elements[index];
            Element* elements2 = &matrix2->elements[index];
            if (elements1->type != elements2->type) {
                return false;
            }
            if (elements1->type == INT) {
                int element1 = *(int*)elements1->data;
                int element2 = *(int*)elements2->data;
                if (element1 != element2) {
                    return false;
                }
            } else {
                float element1 = *(float*)elements1->data;
                float element2 = *(float*)elements2->data;
                if (fabsf(element1 - element2) > FLOAT_EPSILON) {
                    return false;
                }
            }
        }
    }
    return true;
}

void free_test_data(Matrix_test_data* data) {
    if (data) {
        for (size_t i = 0; i < data->matrix_count; i++) {
            free_matrix(&data->matrices[i]);
            free_matrix(&data->transpositions[i]);
        }
        free(data->matrices);
        free(data->transpositions);
        for (size_t i = 0; i < data->sum_count; i++) {
            free_matrix(&data->sums[i]);
        }
        free(data->sums);
        free(data->sum_indexes);
        for (size_t i = 0; i < data->mul_count; i++) {
            free_matrix(&data->multiplications[i]);
        }
        free(data->multiplications);
        free(data->multiplication_indexes);
        for (size_t i = 0; i < data->lin_comb_count; i++) {
            free_matrix(&data->linear_combinations[i]);
        }
        free(data->linear_combinations);
        free(data->linear_combination_params);
    }
}

int read_matrix(FILE* file, Matrix* matrix, Data_type type) {
    size_t rows, cols;
    if (fscanf(file, "%zu %zu", &rows, &cols) != 2) {
        return 0;
    }
    init_matrix(matrix, rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (type == INT) {
                int element;
                if (fscanf(file, "%d", &element) != 1) {
                    return 0;
                }
                int* data = malloc(sizeof(int));
                *data = element;
                add_element(matrix, i, j, data, INT);
            } else if (type == FLOAT) {
                float element;
                if (fscanf(file, "%f", &element) != 1) {
                    return 0;
                }
                float* data = malloc(sizeof(float));
                *data = element;
                add_element(matrix, i, j, data, FLOAT);
            }
        }
    }
    return 1;
}

int read_test_file(const char* filename, Matrix_test_data* data, Data_type type) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return 0;
    }
    char buffer[256];
    if (fscanf(file, "%zu", &data->matrix_count) != 1) {
        fclose(file);
        return 0;
    }
    data->matrices = (Matrix*)malloc(data->matrix_count * sizeof(Matrix));
    for (size_t i = 0; i < data->matrix_count; i++) {
        if (!read_matrix(file, &data->matrices[i], type)) {
            fclose(file);
            return 0;
        }
    }
    if (!fgets(buffer, sizeof(buffer), file) || !fgets(buffer, sizeof(buffer), file) ||
        strstr(buffer, "Transposition results") == NULL) {
        fclose(file);
        return 0;
    }
    data->transpositions = (Matrix*)malloc(data->matrix_count * sizeof(Matrix));
    for (size_t i = 0; i < data->matrix_count; i++) {
        if (!read_matrix(file, &data->transpositions[i], type)) {
            fclose(file);
            return 0;
        }
    }
    if (!fgets(buffer, sizeof(buffer), file) || !fgets(buffer, sizeof(buffer), file) ||
        strstr(buffer, "Sum results") == NULL) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%zu", &data->sum_count) != 1) {
        fclose(file);
        return 0;
    }
    data->sums = (Matrix*)malloc(data->sum_count * sizeof(Matrix));
    data->sum_indexes = (int*)malloc(data->sum_count * 2 * sizeof(int));
    for (size_t i = 0; i < data->sum_count; i++) {
        if (fscanf(file, "%d %d", &data->sum_indexes[i*2], &data->sum_indexes[i*2+1]) != 2) {
            fclose(file);
            return 0;
        }
        if (!read_matrix(file, &data->sums[i], type)) {
            fclose(file);
            return 0;
        }
    }
    if (!fgets(buffer, sizeof(buffer), file) || !fgets(buffer, sizeof(buffer), file) ||
        strstr(buffer, "Multiplication results") == NULL) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%zu", &data->mul_count) != 1) {
        fclose(file);
        return 0;
    }
    data->multiplications = (Matrix*)malloc(data->mul_count * sizeof(Matrix));
    data->multiplication_indexes = (int*)malloc(data->mul_count * 2 * sizeof(int));
    for (size_t i = 0; i < data->mul_count; i++) {
        if (fscanf(file, "%d %d", &data->multiplication_indexes[i*2], &data->multiplication_indexes[i*2+1]) != 2) {
            fclose(file);
            return 0;
        }
        if (!read_matrix(file, &data->multiplications[i], type)) {
            fclose(file);
            return 0;
        }
    }
    if (!fgets(buffer, sizeof(buffer), file) || !fgets(buffer, sizeof(buffer), file) ||
        strstr(buffer, "Linear combination results") == NULL) {
        fclose(file);
        return 0;
    }
    if (fscanf(file, "%zu", &data->lin_comb_count) != 1) {
        fclose(file);
        return 0;
    }
    data->linear_combinations = (Matrix*)malloc(data->lin_comb_count * sizeof(Matrix));
    data->linear_combination_params = (int*)malloc(data->lin_comb_count * 4 * sizeof(int));
    for (size_t i = 0; i < data->lin_comb_count; i++) {
        // Read matrix index, target row, source row, and factor
        if (fscanf(file, "%d %d %d %f",
                   &data->linear_combination_params[i*4],
                   &data->linear_combination_params[i*4+1],
                   &data->linear_combination_params[i*4+2],
                   (float*)&data->linear_combination_params[i*4+3]) != 4) {
            fclose(file);
            return 0;
        }
        if (!read_matrix(file, &data->linear_combinations[i], type)) {
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void run_file_tests(const char* filename, Data_type type) {
    Matrix_test_data test_data = {0};
    if (!read_test_file(filename, &test_data, type)) {
        printf("Failed to read test data\n");
        return;
    }
    Matrix (*sum_func)(Matrix*, Matrix*) = get_sum_function(type);
    Matrix (*mul_func)(Matrix*, Matrix*) = get_multiplication_function(type);
    Matrix (*trans_func)(Matrix*) = get_transposition_function(type);
    Matrix (*lin_comb_func)(Matrix*, size_t, size_t, float) = get_linear_combination_function(type);
    size_t passed_tests = 0;
    size_t total_tests = 0;
    printf("\n=== Transposition Tests ===\n");
    for (size_t i = 0; i < test_data.matrix_count; i++) {
        Matrix transposition_matrices = trans_func(&test_data.matrices[i]);
        printf("Matrix %zu:\n", i+1);
        matrix_output(&test_data.matrices[i]);
        printf("Expected result:\n");
        matrix_output(&test_data.transpositions[i]);
        printf("Actual result:\n");
        matrix_output(&transposition_matrices);
        if (matrix_equality_check(&transposition_matrices, &test_data.transpositions[i])) {
            printf("Test %zu passed\n", i+1);
            passed_tests++;
        } else {
            printf("Test %zu failed\n", i+1);
        }
        total_tests++;
        free_matrix(&transposition_matrices);
    }
    printf("=== Transposition Tests ===\n");
    printf("\n=== Summation Tests ===\n");
    for (size_t i = 0; i < test_data.sum_count; i++) {
        int index1 = test_data.sum_indexes[i*2];
        int index2 = test_data.sum_indexes[i*2+1];
        printf("Matrix1 (M%d):\n", index1+1);
        matrix_output(&test_data.matrices[index1]);
        printf("Matrix2 (M%d):\n", index2+1);
        matrix_output(&test_data.matrices[index2]);
        Matrix sum_matrix = sum_func(&test_data.matrices[index1], &test_data.matrices[index2]);
        printf("Expected result:\n");
        matrix_output(&test_data.sums[i]);
        printf("Actual result:\n");
        matrix_output(&sum_matrix);
        if (matrix_equality_check(&sum_matrix, &test_data.sums[i])) {
            printf("Test %zu (M%d + M%d) passed\n", i+1, index1+1, index2+1);
            passed_tests++;
        } else {
            printf("Test %zu (M%d + M%d) failed\n", i+1, index1+1, index2+1);
        }
        total_tests++;
        free_matrix(&sum_matrix);
    }
    printf("=== Summation Tests ===\n");
    printf("\n=== Multiplication Tests ===\n");
    for (size_t i = 0; i < test_data.mul_count; i++) {
        int index1 = test_data.multiplication_indexes[i*2];
        int index2 = test_data.multiplication_indexes[i*2+1];
        printf("Matrix1 (M%d):\n", index1+1);
        matrix_output(&test_data.matrices[index1]);
        printf("Matrix2 (M%d):\n", index2+1);
        matrix_output(&test_data.matrices[index2]);
        Matrix multiplication_matrix = mul_func(&test_data.matrices[index1], &test_data.matrices[index2]);
        printf("Expected result:\n");
        matrix_output(&test_data.multiplications[i]);
        printf("Actual result:\n");
        matrix_output(&multiplication_matrix);
        if (matrix_equality_check(&multiplication_matrix, &test_data.multiplications[i])) {
            printf("Test %zu (M%d * M%d) passed\n", i+1, index1+1, index2+1);
            passed_tests++;
        } else {
            printf("Test %zu (M%d * M%d) failed\n", i+1, index1+1, index2+1);
        }
        total_tests++;
        free_matrix(&multiplication_matrix);
    }
    printf("=== Multiplication Tests ===\n");
    printf("\n=== Linear Combination Tests ===\n");
    for (size_t i = 0; i < test_data.lin_comb_count; i++) {
        int matrix_index = test_data.linear_combination_params[i*4];
        int target_row = test_data.linear_combination_params[i*4+1];
        int source_row = test_data.linear_combination_params[i*4+2];
        float factor = *(float*)&test_data.linear_combination_params[i*4+3];
        printf("Matrix (M%d):\n", matrix_index+1);
        matrix_output(&test_data.matrices[matrix_index]);
        printf("Operation: Add to row %d a linear combination of row %d with factor %.2f\n", target_row, source_row, factor);
        Matrix lin_comb_matrix = lin_comb_func(&test_data.matrices[matrix_index], target_row, source_row, factor);
        printf("Expected result:\n");
        matrix_output(&test_data.linear_combinations[i]);
        printf("Actual result:\n");
        matrix_output(&lin_comb_matrix);
        if (matrix_equality_check(&lin_comb_matrix, &test_data.linear_combinations[i])) {
            printf("Test %zu passed\n", i+1);
            passed_tests++;
        } else {
            printf("Test %zu failed\n", i+1);
        }
        total_tests++;
        free_matrix(&lin_comb_matrix);
    }
    printf("=== Linear Combination Tests ===\n");
    printf("\n=== Test Summary ===\n");
    printf("Passed: %zu/%zu (%.2f%%)\n", passed_tests, total_tests, (float)passed_tests / total_tests * 100);
    free_test_data(&test_data);
}