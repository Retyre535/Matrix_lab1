#include <stdio.h>
#include "Matrix.h"
#include "Tests.h"

void transactions(int transaction, Data_type type) {
    Matrix matrix1, matrix2, result_matrix;
    switch (transaction) {
            case 1:
                printf("Input 1 matrix");
                matrix_input(&matrix1, type);
                printf("Input 2 matrix");
                matrix_input(&matrix2, type);
                result_matrix = matrices_sum(&matrix1, &matrix2);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                free_matrix(&result_matrix);
                break;
            case 2:
                printf("Input 1 matrix");
                matrix_input(&matrix1, type);
                printf("Input 2 matrix");
                matrix_input(&matrix2, type);
                result_matrix = matrix_multiplication(&matrix1, &matrix2);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&matrix2);
                free_matrix(&result_matrix);
                break;
            case 3:
                printf("Input matrix");
                matrix_input(&matrix1, type);
                result_matrix = transposition_matrix(&matrix1);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&result_matrix);
                break;
            case 4:
                int target, source;
                float factor;
                printf("Input matrix");
                matrix_input(&matrix1, type);
                printf("Enter which line to add to: ");
                scanf("%d", &target);
                printf("enter which line to add: ");
                scanf("%d", &source);
                printf("Enter multiplier: ");
                scanf("%f", &factor);
                result_matrix = add_linear_combination_to_row(&matrix1, target, source, factor);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&result_matrix);
                break;
            default:
                run_file_tests("C:\\Users\\JDubo\\CLionProjects\\untitled\\tests_matrices_int.txt", INT);
                run_file_tests("C:\\Users\\JDubo\\CLionProjects\\untitled\\tests_matrices_float.txt", FLOAT);
                break;
        }

}

int main(void) {
    int exit_code = 0;
    while (exit_code == 0) {
        int transaction, type_code = 1;
        Data_type data_type = INT;
        printf("Enter transaction code: \n1 - matrix addition\n2 - matrix multiplication\n3 - transposition\n4 - adding to a string a linear combination of other strings\nOther - default tests\n:");
        scanf("%d", &transaction);
        if (transaction>=1 && transaction<=4) {
            printf("\nChoose type 1 - Int, 2 - Float: ");
            scanf("%d", &type_code);
        }
        if (type_code == 1) {
            data_type = INT;
        } else if (type_code == 2) {
            data_type = FLOAT;
        } else {
            printf("Wrong type code");
            transaction = 5;
        }
        transactions(transaction, data_type);
        printf("Do you want to continue? (if yes 0/else 1): ");
        scanf("%d", &exit_code);
    }
    printf("\n Execution completed");
}
