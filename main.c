#include <stdio.h>
#include <stdlib.h>

#include "matrix_functions.h"
#include "integer_type.h"
#include "double_type.h"

#define MAX_MATRICES 3
#define MAT_A 0
#define MAT_B 1
#define MAT_C 2

// Матрицы: A, B, C
static Matrix matrices[MAX_MATRICES];
static int is_initialized[MAX_MATRICES] = {0}; // 1 если инициализирована
static const char* mat_names[] = {"A", "B", "C"};

// Освобождение всех матриц перед выходом
static void cleanup() {
    for (int i = 0; i < MAX_MATRICES; i++) {
        if (is_initialized[i]) {
            deleteMatrix(&matrices[i]);
            is_initialized[i] = 0;
        }
    }
    deleteIntegerTypeInfo();
    deleteDoubleTypeInfo();
}

// Инициализация матрицы с выбором типа
static int create_matrix(int idx, int rows, int cols, int type_int) {
    if (idx < 0 || idx >= MAX_MATRICES) return -1;
    if (is_initialized[idx]) {
        deleteMatrix(&matrices[idx]);
        is_initialized[idx] = 0;
    }
    const TypeInfo* info = type_int ? getIntegerTypeInfo() : getDoubleTypeInfo();
    int ret = initMatrix(&matrices[idx], rows, cols, info);
    if (ret == MATRIX_OK) {
        is_initialized[idx] = 1;
    }
    return ret;
}

// Установка элемента
static int set_elem(int idx, int row, int col, void* value, int type_int) {
    if (idx < 0 || idx >= MAX_MATRICES || !is_initialized[idx]) return -1;
    return setMatrixElem(&matrices[idx], col, row, value); // setMatrixElem ожидает (colon, line)
}

// Печать
static void print_mat(int idx) {
    if (idx < 0 || idx >= MAX_MATRICES || !is_initialized[idx]) {
        printf("Matrix not initialized\n");
        return;
    }
    printMatrix(&matrices[idx]);
    printf("\n");
}

int main() {
    printf("=== Matrix Calculator (simplified) ===\n");
    printf("Operations:\n");
    printf("  1: Create matrix\n");
    printf("     -> input: matrix name (A/B/C), rows, cols, type (1=int, 0=double)\n");
    printf("  2: Set element\n");
    printf("     -> input: matrix name (A/B/C), row index (0-based), col index (0-based), type (1/0), value\n");
    printf("  3: Print matrix\n");
    printf("     -> input: matrix name (A/B/C)\n");
    printf("  4: Sum (A + B -> C)\n");
    printf("     -> no additional input, assumes A and B exist\n");
    printf("  5: Multiply (A * B -> C)\n");
    printf("     -> no additional input, assumes A and B exist\n");
    printf("  6: Transpose (A -> C)\n");
    printf("     -> no additional input, assumes A exists\n");
    printf("  7: Line add (add coefficients to a row of A)\n");
    printf("     -> input: line number (1-based), then coefficients for all rows (integer or double)\n");
    printf("  0: Exit\n");


    int choice;
    while (1) {
        printf("\n> ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 0) break;

        if (choice == 1) {
            char mat_name[10];
            int rows, cols, type;
            printf("Matrix (A/B/C): ");
            scanf("%9s", mat_name);
            printf("Rows Cols: ");
            scanf("%d %d", &rows, &cols);
            printf("Type (1=int, 0=double): ");
            scanf("%d", &type);
            int idx = -1;
            if (mat_name[0] == 'A') idx = MAT_A;
            else if (mat_name[0] == 'B') idx = MAT_B;
            else if (mat_name[0] == 'C') idx = MAT_C;
            else { printf("Invalid matrix\n"); continue; }
            int ret = create_matrix(idx, rows, cols, type);
            if (ret == MATRIX_OK) printf("Matrix %s created\n", mat_name);
            else printf("Creation failed (code %d)\n", ret);
        }
        else if (choice == 2) {
            char mat_name[10];
            int row, col, type;
            printf("Matrix (A/B/C): ");
            scanf("%9s", mat_name);
            printf("Row Col: ");
            scanf("%d %d", &row, &col);
            printf("Type (1=int, 0=double): ");
            scanf("%d", &type);
            int idx = -1;
            if (mat_name[0] == 'A') idx = MAT_A;
            else if (mat_name[0] == 'B') idx = MAT_B;
            else if (mat_name[0] == 'C') idx = MAT_C;
            else { printf("Invalid matrix\n"); continue; }
            if (!is_initialized[idx]) {
                printf("Matrix not initialized\n");
                continue;
            }
            if (type == 1) {
                int val;
                printf("Value: ");
                scanf("%d", &val);
                Integer v = {val};
                int ret = set_elem(idx, row, col, &v, 1);
                if (ret == MATRIX_OK) printf("Element set\n");
                else printf("Set error (code %d)\n", ret);
            } else {
                double val;
                printf("Value: ");
                scanf("%lf", &val);
                Double v = {val};
                int ret = set_elem(idx, row, col, &v, 0);
                if (ret == MATRIX_OK) printf("Element set\n");
                else printf("Set error (code %d)\n", ret);
            }
        }
        else if (choice == 3) {
            char mat_name[10];
            printf("Matrix (A/B/C): ");
            scanf("%9s", mat_name);
            int idx = -1;
            if (mat_name[0] == 'A') idx = MAT_A;
            else if (mat_name[0] == 'B') idx = MAT_B;
            else if (mat_name[0] == 'C') idx = MAT_C;
            else { printf("Invalid matrix\n"); continue; }
            print_mat(idx);
        }
        else if (choice == 4) { // sum A+B -> C
            if (!is_initialized[MAT_A] || !is_initialized[MAT_B]) {
                printf("A or B not initialized\n");
                continue;
            }
            if (matrices[MAT_A].info != matrices[MAT_B].info) {
                printf("Type mismatch\n");
                continue;
            }
            // Освобождаем C, если была
            if (is_initialized[MAT_C]) deleteMatrix(&matrices[MAT_C]);
            int ret = sumMatrix(&matrices[MAT_A], &matrices[MAT_B], &matrices[MAT_C]);
            if (ret == MATRIX_OK) {
                is_initialized[MAT_C] = 1;
                matrices[MAT_C].info = matrices[MAT_A].info; // initMatrix уже установила
                printf("Sum stored in C\n");
            } else {
                printf("Sum error (code %d)\n", ret);
                is_initialized[MAT_C] = 0;
            }
        }
        else if (choice == 5) { // multiply A*B -> C
            if (!is_initialized[MAT_A] || !is_initialized[MAT_B]) {
                printf("A or B not initialized\n");
                continue;
            }
            if (matrices[MAT_A].info != matrices[MAT_B].info) {
                printf("Type mismatch\n");
                continue;
            }
            if (is_initialized[MAT_C]) deleteMatrix(&matrices[MAT_C]);
            int ret = multMatrix(&matrices[MAT_A], &matrices[MAT_B], &matrices[MAT_C]);
            if (ret == MATRIX_OK) {
                is_initialized[MAT_C] = 1;
                matrices[MAT_C].info = matrices[MAT_A].info;
                printf("Product stored in C\n");
            } else {
                printf("Multiplication error (code %d)\n", ret);
                is_initialized[MAT_C] = 0;
            }
        }
        else if (choice == 6) { // transpose A -> C
            if (!is_initialized[MAT_A]) {
                printf("A not initialized\n");
                continue;
            }
            if (is_initialized[MAT_C]) deleteMatrix(&matrices[MAT_C]);
            int ret = transMatrix(&matrices[MAT_A], &matrices[MAT_C]);
            if (ret == MATRIX_OK) {
                is_initialized[MAT_C] = 1;
                matrices[MAT_C].info = matrices[MAT_A].info;
                printf("Transpose stored in C\n");
            } else {
                printf("Transpose error (code %d)\n", ret);
                is_initialized[MAT_C] = 0;
            }
        }
        else if (choice == 7) { // line add to A
            if (!is_initialized[MAT_A]) {
                printf("A not initialized\n");
                continue;
            }
            int line;
            printf("Line (1-based): ");
            scanf("%d", &line);
            int rows = matrices[MAT_A].height;
            if (matrices[MAT_A].info == getIntegerTypeInfo()) {
                int coeffs[rows];
                printf("Enter %d coefficients: ", rows);
                for (int i = 0; i < rows; i++) scanf("%d", &coeffs[i]);
                int ret = lineAddMatrix(&matrices[MAT_A], line, coeffs);
                if (ret == MATRIX_OK) printf("Line addition done\n");
                else printf("Line add error (code %d)\n", ret);
            } else {
                double coeffs[rows];
                printf("Enter %d coefficients: ", rows);
                for (int i = 0; i < rows; i++) scanf("%lf", &coeffs[i]);
                int ret = lineAddMatrix(&matrices[MAT_A], line, coeffs);
                if (ret == MATRIX_OK) printf("Line addition done\n");
                else printf("Line add error (code %d)\n", ret);
            }
        }
        else {
            printf("Unknown option\n");
        }

        // очистка буфера ввода
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    cleanup();
    printf("Bye\n");
    return 0;
}