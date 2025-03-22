#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

void transactions(int transaction) {
    Matrix matrix1, matrix2, result_matrix;
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
                int target, source;
                float factor;
                printf("Input matrix");
                matrix_input(&matrix1, INT);
                printf("Enter which line to add to: ");
                scanf("%d", &target);
                printf("enter which line to add: ");
                scanf("%d", &source);
                printf("Enter multiplier: ");
                scanf("%d", &factor);
                result_matrix = add_linear_combination_to_row(&matrix1, target, source, factor);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&result_matrix);
                break;
            default:
                printf("Wrong transaction code");
                break;
        }

}

int main(void) {
    int exit_code = 0;
    while (exit_code == 0) {
        int transaction;
        printf("Enter transaction code: \n1 - matrix addition\n2 - matrix multiplication\n3 - transposition\n4 - adding to a string a linear combination of other strings\nOther - default tests\n:");
        scanf("%d", &transaction);
        transactions(transaction);
        printf("Do you want to continue? (if yes 0/else 1): ");
        scanf("%d", &exit_code);
    }
    printf("\n Execution completed");
}
