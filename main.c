#include <stdio.h>
#include "Matrix.h"
#include "Tests.h"

void transactions(int transaction, Data_type type) {
    Matrix matrix1, matrix2, result_matrix;
    Matrix (*sum_func)(Matrix*, Matrix*) = get_sum_function(type);
    Matrix (*mul_func)(Matrix*, Matrix*) = get_multiplication_function(type);
    Matrix (*trans_func)(Matrix*) = get_transposition_function(type);
    void (*input_func)(Matrix*) = get_input_function(type);
    Matrix (*lin_comb_func)(Matrix*, size_t, size_t, float) = get_linear_combination_function(type);
    switch (transaction) {
        case 1:
            printf("Input 1 matrix");
            input_func(&matrix1);
            printf("Input 2 matrix");
            input_func(&matrix2);
            result_matrix = sum_func(&matrix1, &matrix2);
            matrix_output(&result_matrix);
            free_matrix(&matrix1);
            free_matrix(&matrix2);
            free_matrix(&result_matrix);
            break;
        case 2:
            printf("Input 1 matrix");
            input_func(&matrix1);
            printf("Input 2 matrix");
            input_func(&matrix2);
            result_matrix = mul_func(&matrix1, &matrix2);
            matrix_output(&result_matrix);
            free_matrix(&matrix1);
            free_matrix(&matrix2);
            free_matrix(&result_matrix);
            break;
        case 3:
            printf("Input matrix");
            input_func(&matrix1);
            result_matrix = trans_func(&matrix1);
            matrix_output(&result_matrix);
            free_matrix(&matrix1);
            free_matrix(&result_matrix);
            break;
        case 4:
            {
                int target, source;
                float factor;
                printf("Input matrix");
                input_func(&matrix1);
                printf("Enter which line to add to: ");
                scanf("%d", &target);
                printf("enter which line to add: ");
                scanf("%d", &source);
                printf("Enter multiplier: ");
                scanf("%f", &factor);
                result_matrix = lin_comb_func(&matrix1, target, source, factor);
                matrix_output(&result_matrix);
                free_matrix(&matrix1);
                free_matrix(&result_matrix);
            }
            break;
        default:
            run_file_tests("C:\\Users\\JDubo\\CLionProjects\\untitled\\tests_matrices_int.txt", INT);
            run_file_tests("C:\\Users\\JDubo\\CLionProjects\\untitled\\tests_matrices_float.txt", FLOAT);
            break;
    }
}

int main(void) {
    int exit_code = 0;
    while (exit_code != 1) {
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
    return 0;
}