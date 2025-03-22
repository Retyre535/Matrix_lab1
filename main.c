#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(void) {
    int exit_code = 0;
    while (exit_code == 0) {
        Matrix matrix1, matrix2, result_matrix;
        int rows_matrix1 = 0, cols_matrix1 = 0, cols_matrix2 = 0, rows_matrix2 = 0, transaction;
        printf("Enter transaction code: \n1 - matrix addition\n2 - matrix multiplication\n3 - transposition\n4 - adding to a string a linear combination of other strings\n:");
        scanf("%d", &transaction);
        switch (transaction) {
            case 1:
                printf("Input 1 matrix");
                matrix_input(&matrix1, INT);
                printf("Input 2 matrix");
                matrix_input(&matrix2, INT);
                result_matrix = matrices_sum(&matrix1, &matrix2);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                free_matrix(&result_matrix);
                break;
            case 2:
                printf("Input 1 matrix");
                matrix_input(&matrix1, INT);
                printf("Input 2 matrix");
                matrix_input(&matrix2, INT);
                result_matrix = matrix_multiplication(&matrix1, &matrix2);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                free_matrix(&result_matrix);
                break;
            case 3:
                printf("Input matrix");
                matrix_input(&matrix1, INT);
                result_matrix = transposition_matrix(&matrix1);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&result_matrix);
                break;
            case 4:
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
