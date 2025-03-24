#include "Tests.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

Matrix int_matrix1, int_matrix2, int_matrix3, int_matrix4, int_matrix5, int_matrix6, int_matrix7;
Matrix matrix1, matrix2, matrix3, matrix4, matrix5, matrix6, matrix7;
Matrix result_int_transposition1, result_int_transposition2, result_int_transposition3,
result_int_transposition4, result_int_transposition5, result_int_transposition6, result_int_transposition7;

bool matrix_equality_check(Matrix* matrix1, Matrix* matrix2) {
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        return false;
    }
    for (size_t i = 0; i < matrix1->rows; i++) {
        for (size_t j = 0; j < matrix1->cols; j++) {
            size_t index = i * matrix1->cols + j;
            if (matrix1->elements[index].type != matrix2->elements[index].type) {
                return false;
            }
            if (matrix1->elements[index].type == INT) {
                int* elements1 = (int*)matrix1->elements[index].data;
                int* elements2 = (int*)matrix2->elements[index].data;
                if (*elements1 != *elements2) {
                    return false;
                }
            } else if (matrix1->elements[index].type == FLOAT) {
                float* elements1 = (float*)matrix1->elements[index].data;
                float* elements2 = (float*)matrix2->elements[index].data;
                if (*elements1 != *elements2) {
                    return false;
                }
            }
        }
    }
    return true;
}

void create_int_matrices() {
    init_matrix(&int_matrix1, 1, 1);
    init_matrix(&int_matrix2, 2, 2);
    init_matrix(&int_matrix3, 3, 3);
    init_matrix(&int_matrix4, 4, 4);
    init_matrix(&int_matrix5, 2, 1);
    init_matrix(&int_matrix6, 3, 2);
    init_matrix(&int_matrix7, 2, 3);

    add_element(&int_matrix1, 0, 0, 1, INT);

    add_element(&int_matrix2, 0, 0, 1, INT);
    add_element(&int_matrix2, 0, 1, 2, INT);
    add_element(&int_matrix2, 1, 0, 3, INT);
    add_element(&int_matrix2, 1, 1, 4, INT);

    add_element(&int_matrix3, 0, 0, 1, INT);
    add_element(&int_matrix3, 0, 1, 2, INT);
    add_element(&int_matrix3, 0, 2, 3, INT);
    add_element(&int_matrix3, 1, 0, 4, INT);
    add_element(&int_matrix3, 1, 1, 5, INT);
    add_element(&int_matrix3, 1, 2, 6, INT);
    add_element(&int_matrix3, 2, 0, 7, INT);
    add_element(&int_matrix3, 2, 1, 8, INT);
    add_element(&int_matrix3, 2, 2, 9, INT);

    add_element(&int_matrix4, 0, 0, 1, INT);
    add_element(&int_matrix4, 0, 1, 2, INT);
    add_element(&int_matrix4, 0, 2, 3, INT);
    add_element(&int_matrix4, 0, 3, 4, INT);
    add_element(&int_matrix4, 1, 0, 5, INT);
    add_element(&int_matrix4, 1, 1, 6, INT);
    add_element(&int_matrix4, 1, 2, 7, INT);
    add_element(&int_matrix4, 1, 3, 8, INT);
    add_element(&int_matrix4, 2, 0, 8, INT);
    add_element(&int_matrix4, 2, 1, 0, INT);
    add_element(&int_matrix4, 2, 2, 1, INT);
    add_element(&int_matrix4, 2, 3, 2, INT);
    add_element(&int_matrix4, 3, 0, 3, INT);
    add_element(&int_matrix4, 3, 1, 4, INT);
    add_element(&int_matrix4, 3, 2, 5, INT);
    add_element(&int_matrix4, 3, 3, 6, INT);

    add_element(&int_matrix5, 0, 0, 1, INT);
    add_element(&int_matrix5, 1, 0, 2, INT);

    add_element(&int_matrix6, 0, 0, 1, INT);
    add_element(&int_matrix6, 0, 1, 2, INT);
    add_element(&int_matrix6, 1, 0, 3, INT);
    add_element(&int_matrix6, 1, 1, 7, INT);
    add_element(&int_matrix6, 2, 1, 8, INT);
    add_element(&int_matrix6, 2, 2, 9, INT);

    add_element(&int_matrix7, 0, 0, 4, INT);
    add_element(&int_matrix7, 0, 1, 5, INT);
    add_element(&int_matrix7, 0, 2, 6, INT);
    add_element(&int_matrix7, 1, 0, 7, INT);
    add_element(&int_matrix7, 1, 1, 8, INT);
    add_element(&int_matrix7, 1, 2, 9, INT);
}

void create_result_int_matrices_transposition() {
    init_matrix(&result_int_transposition1, 1, 1);
    init_matrix(&result_int_transposition2, 2, 2);
    init_matrix(&result_int_transposition3, 3, 3);
    init_matrix(&result_int_transposition4, 4, 4);
    init_matrix(&result_int_transposition5, 1, 2);
    init_matrix(&result_int_transposition6, 2, 3);
    init_matrix(&result_int_transposition7, 3, 2);

    add_element(&result_int_transposition1, 0, 0, 1, INT);

    add_element(&result_int_transposition2, 0, 0, 1, INT);
    add_element(&result_int_transposition2, 1, 0, 2, INT);
    add_element(&result_int_transposition2, 0, 1, 3, INT);
    add_element(&result_int_transposition2, 1, 1, 4, INT);

    add_element(&result_int_transposition3, 0, 0, 1, INT);
    add_element(&result_int_transposition3, 1, 0, 2, INT);
    add_element(&result_int_transposition3, 2, 0, 3, INT);
    add_element(&result_int_transposition3, 0, 1, 4, INT);
    add_element(&result_int_transposition3, 1, 1, 5, INT);
    add_element(&result_int_transposition3, 2, 1, 6, INT);
    add_element(&result_int_transposition3, 0, 2, 7, INT);
    add_element(&result_int_transposition3, 1, 2, 8, INT);
    add_element(&result_int_transposition3, 2, 2, 9, INT);

    add_element(&result_int_transposition4, 0, 0, 1, INT);
    add_element(&result_int_transposition4, 1, 0, 2, INT);
    add_element(&result_int_transposition4, 2, 0, 3, INT);
    add_element(&result_int_transposition4, 3, 0, 4, INT);
    add_element(&result_int_transposition4, 0, 1, 5, INT);
    add_element(&result_int_transposition4, 1, 1, 6, INT);
    add_element(&result_int_transposition4, 2, 1, 7, INT);
    add_element(&result_int_transposition4, 3, 1, 8, INT);
    add_element(&result_int_transposition4, 0, 2, 9, INT);
    add_element(&result_int_transposition4, 1, 2, 0, INT);
    add_element(&result_int_transposition4, 2, 2, 1, INT);
    add_element(&result_int_transposition4, 3, 2, 2, INT);
    add_element(&result_int_transposition4, 0, 3, 3, INT);
    add_element(&result_int_transposition4, 1, 3, 4, INT);
    add_element(&result_int_transposition4, 2, 3, 5, INT);
    add_element(&result_int_transposition4, 3, 3, 6, INT);

    add_element(&result_int_transposition5, 0, 0, 1, INT);
    add_element(&result_int_transposition5, 0, 1, 2, INT);

    add_element(&result_int_transposition6, 0, 0, 1, INT);
    add_element(&result_int_transposition6, 1, 0, 2, INT);
    add_element(&result_int_transposition6, 0, 1, 3, INT);
    add_element(&result_int_transposition6, 1, 1, 7, INT);
    add_element(&result_int_transposition6, 0, 2, 8, INT);
    add_element(&result_int_transposition6, 1, 2, 9, INT);

    add_element(&result_int_transposition7, 0, 0, 4, INT);
    add_element(&result_int_transposition7, 0, 1, 7, INT);
    add_element(&result_int_transposition7, 1, 0, 5, INT);
    add_element(&result_int_transposition7, 1, 1, 8, INT);
    add_element(&result_int_transposition7, 2, 0, 6, INT);
    add_element(&result_int_transposition7, 2, 1, 9, INT);
}

void transposition_int_tests() {
    init_matrix(&matrix1, 1, 1);
    init_matrix(&matrix2, 2, 2);
    init_matrix(&matrix3, 3, 3);
    init_matrix(&matrix4, 4, 4);
    init_matrix(&matrix5, 1, 2);
    init_matrix(&matrix6, 2, 3);
    init_matrix(&matrix7, 3, 2);
    bool results[7];
    create_int_matrices();
    create_result_int_matrices_transposition();
    matrix1 = transposition_matrix(&int_matrix1);
    matrix2 = transposition_matrix(&int_matrix2);
    matrix3 = transposition_matrix(&int_matrix3);
    matrix4 = transposition_matrix(&int_matrix4);
    matrix5 = transposition_matrix(&int_matrix5);
    matrix6 = transposition_matrix(&int_matrix6);
    matrix7 = transposition_matrix(&int_matrix7);
    printf("Here0");
    results[0] = matrix_equality_check(&matrix1, &result_int_transposition1);
    results[1] = matrix_equality_check(&matrix2, &result_int_transposition2);
    results[2] = matrix_equality_check(&matrix3, &result_int_transposition3);
    results[3] = matrix_equality_check(&matrix4, &result_int_transposition4);
    results[4] = matrix_equality_check(&matrix5, &result_int_transposition5);
    results[5] = matrix_equality_check(&matrix6, &result_int_transposition6);
    results[6] = matrix_equality_check(&matrix7, &result_int_transposition7);
    printf("HERE");
    for (int i = 0; i<7; i++) {
        if (results[i]) {
            printf("%d, %s", i, "transposition test passed\n");
        } else {
            printf("%d, %s", i, "transposition test failed\n");
        }
    }

    free_matrix(&matrix1);
    free_matrix(&matrix2);
    free_matrix(&matrix3);
    free_matrix(&matrix4);
    free_matrix(&matrix5);
    free_matrix(&matrix6);
    free_matrix(&matrix7);
    free_matrix(&int_matrix1);
    free_matrix(&int_matrix2);
    free_matrix(&int_matrix3);
    free_matrix(&int_matrix4);
    free_matrix(&int_matrix5);
    free_matrix(&int_matrix6);
    free_matrix(&int_matrix7);
    free_matrix(&result_int_transposition1);
    free_matrix(&result_int_transposition2);
    free_matrix(&result_int_transposition3);
    free_matrix(&result_int_transposition4);
    free_matrix(&result_int_transposition5);
    free_matrix(&result_int_transposition6);
    free_matrix(&result_int_transposition7);
}
