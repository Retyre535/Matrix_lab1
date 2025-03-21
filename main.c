#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INT, FLOAT
}Data_type;

typedef struct {
    void* data;
    Data_type type;
} Element;

typedef struct {
    Element* elements;
    size_t rows;
    size_t cols;
} Matrix;

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
        exit(1);
    } else {
        for (size_t i = 0; i <= matrix1->rows; i++) {
            for (size_t j = 0; j <= matrix2->cols; j++) {
                size_t index = i * matrix1->cols + j;
                result.elements[index].type = matrix1->elements[index].type;
                if (matrix1->elements[index].type == INT && matrix2->elements[index].type == INT) {
                    int* a = (int*)matrix1->elements[i].data;
                    int* b = (int*)matrix2->elements[i].data;
                    int* sum = malloc(sizeof(int));
                    *sum = *a + *b;
                    result.elements[index].data = sum;
                } else if (matrix1->elements[i].type == FLOAT && matrix2->elements[i].type == FLOAT) {
                    float* a = (float*)matrix1->elements[i].data;
                    float* b = (float*)matrix2->elements[i].data;
                    float* sum = malloc(sizeof(float));
                    *sum = *a + *b;
                    result.elements[index].data = sum;
                } else {
                    printf("Different matrices elements types");
                    exit(1);
                }
            }
        }
    }
    return result;
}

Matrix transposition_matrix(const Matrix* matrix) {
    Matrix result;
    init_matrix(&result, matrix->cols, matrix->rows);
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            size_t old_index = i * matrix->cols + j;
            size_t new_index = j * matrix->cols + i;
            result.elements[old_index].type = matrix->elements[new_index].type;
            if (matrix->elements[new_index].type == INT) {
                int* a = (int*)matrix->elements[old_index].data;
                int* b = malloc(sizeof(int));
                *b = *a;
                result.elements[new_index].data = b;
            }
            else if (matrix->elements[new_index].type == FLOAT) {
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
                printf("%d ", matrix->elements[index].data);
            } else if (matrix->elements[index].type == FLOAT) {
                printf("%.2f ", matrix->elements[index].data);
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
    if (matrix1->rows != matrix2->cols) {
        printf("Multiplication is not possible due to the matrix sizes.");
        exit(1);
    }
    Matrix result;
    init_matrix(&result, matrix1->rows, matrix2->cols);
    for (size_t i = 0; i < matrix1->rows; i++) {
        for (size_t j = 0; j < matrix2->cols; j++) {
            size_t index = i * matrix1->cols + j;
            result.elements[index].type = matrix1->elements[index].type;
            if (matrix1->elements[index].type == INT) {
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

int main(void) {
    int exit_code = 0;
    while (exit_code == 0) {
        Matrix matrix1, matrix2, result_matrix;
        int rows_matrix1 = 0, cols_matrix1 = 0, cols_matrix2 = 0, rows_matrix2 = 0, transaction;
        printf("Enter transaction code: \n1 - matrix addition\n2 - matrix multiplication\n3 - transposition\n4 - adding to a string a linear combination of other strings\n:");
        scanf("%d", &transaction);
        switch (transaction) {
            case 1:
                printf("Enter matrix sizes separated by spaces: ");
                scanf("%d %d %d %d", &rows_matrix1, &cols_matrix1, &rows_matrix2, &cols_matrix2);
                init_matrix(&matrix1, rows_matrix1, cols_matrix1);
                init_matrix(&matrix2, rows_matrix2, cols_matrix2);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                break;
            case 2:
                printf("Enter matrix sizes separated by spaces: ");
                scanf("%d %d %d %d", &rows_matrix1, &cols_matrix1, &rows_matrix2, &cols_matrix2);
                init_matrix(&matrix1, rows_matrix1, cols_matrix1);
                init_matrix(&matrix2, rows_matrix2, cols_matrix2);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                break;
            case 3:
                printf("Enter matrix dimensions separated by spaces: ");
                scanf("%d %d", &rows_matrix1, &cols_matrix1);
                init_matrix(&matrix1, rows_matrix1, cols_matrix1);
                free_matrix(&matrix1);
                break;
            case 4:
                printf("Enter matrix dimensions separated by spaces: ");
                scanf("%d %d", &rows_matrix1, &cols_matrix1);
                init_matrix(&matrix1, rows_matrix1, cols_matrix1);
                free_matrix(&matrix1);
                break;
            default:
                printf("Wrong transaction code");
                break;
        }
        printf("Do you want to continue? (if yes 0/else 1): ");
        scanf("%d", &exit_code);
    }
    printf("\n Execution completed");
}