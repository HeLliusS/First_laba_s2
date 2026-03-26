#include <stdio.h>
#include <stdlib.h>

#include "matrix_type.h"

void setMatrixElem(Matrix* matrix, const int colon, const int line, const void* value) {
    if (colon > matrix->length || colon < 0 || line > matrix->height || line < 0) {
        printf("Coord is out of range");
        return;
    }

    matrix->info->set(value, matrix->value + (colon + line * matrix->length) * sizeof(void*));
}

void printMatrix(const Matrix* matrix) {
    int coordLength = 0, coordHeight = 0;
    int coord = 0;

    for (coordHeight = 0; coordHeight < matrix->height; coordHeight++) {
        for (coordLength = 0; coordLength < matrix->length; coordLength++) {
            coord = (coordLength + coordHeight * matrix->length) * sizeof(void*);

            matrix->info->print(matrix->value + coord);

            if (coordLength + 1 != matrix->length) printf(" ");
        }
        printf("\n");
    }
}

void sumMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if ((first->length != second->length) || (first->height != second->height)) {
        printf("Wrong size of Matrix");
        return;
    }

    if ((first->info != second->info)) {
        printf("Types of Matrix elements do not match");
        return;
    }

    initMatrix(newMatrix, first->height, first->length, first->info);

    int coordLength = 0, coordHeight = 0, length = first->length, height = first->height;
    int coord = 0;

    for (coordHeight = 0; coordHeight < height; coordHeight++) {
        for (coordLength = 0; coordLength < length; coordLength++) {
            coord = (coordLength + coordHeight * length) * sizeof(void*);
            first->info->add((first->value + coord), (second->value + coord), (newMatrix->value + coord));
        }
    }
}

void multMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if ((first->length != second->height)) {
        printf("Wrong size of Matrix");
        return;
    }

    if ((first->info != second->info)) {
        printf("Types of Matrix elements do not match");
        return;
    }

    initMatrix(newMatrix, first->height, second->length, first->info);

    int coordNewLength = 0, coordNewHeight = 0, coordSlip = 0;
    int coord = 0, coordFirst = 0, coordSecond = 0;
    void* timelyMult = malloc(newMatrix->info->elemSize);

    for (coordNewLength = 0; coordNewLength < newMatrix->length; coordNewLength++) {
        for (coordNewHeight = 0; coordNewHeight < newMatrix->height; coordNewHeight++) {
            coord = (coordNewLength + coordNewHeight * newMatrix->length) * sizeof(void*);
            newMatrix->info->set(newMatrix->info->neutralElemAdd, newMatrix->value + coord);

            for (coordSlip = 0; coordSlip < first->length; coordSlip++) {
                coordFirst = (coordNewHeight * first->length + coordSlip) * sizeof(void*);
                coordSecond = (coordNewLength + second->length * coordSlip) * sizeof(void*);
                newMatrix->info->mult(first->value + coordFirst, second->value + coordSecond, timelyMult);

                newMatrix->info->add(newMatrix->value + coord, timelyMult, newMatrix->value + coord);
            }
        }
    }

    free(timelyMult);
}

void transMatrix(const Matrix* matrix, Matrix* newMatrix) {
    initMatrix(newMatrix, matrix->length, matrix->height, matrix->info);

    int coordLengthNew = 0, coordHeightNew = 0;
    int coordNew = 0, coordMatrix = 0;

    for (coordHeightNew = 0; coordHeightNew < newMatrix->height; coordHeightNew++) {
        for (coordLengthNew = 0; coordLengthNew < newMatrix->length; coordLengthNew++) {
            coordNew = (coordHeightNew * newMatrix->length + coordLengthNew) * sizeof(void*);
            coordMatrix = (coordLengthNew * matrix->length + coordHeightNew) * sizeof(void*);
            newMatrix->info->set(matrix->value + coordMatrix, newMatrix->value + coordNew);
        }
    }
}

void lineAddMatrix(Matrix* matrix, const int line, const void* cfs) {
    int addLine = 0, addColon = 0;
    int coordChange = 0, coordGet = 0;
    void* timelyMult = malloc(matrix->info->elemSize);

    for (addLine = 0; addLine < matrix->height; addLine++) {
        for (addColon = 0; addColon < matrix->length; addColon++) {
            coordChange = ((line - 1) * matrix->length + addColon) * sizeof(void*);
            coordGet = (addLine * matrix->length + addColon) * sizeof(void*);
            matrix->info->mult(cfs + addLine * matrix->info->elemSize, matrix->value + coordGet, timelyMult);
            matrix->info->add(timelyMult, matrix->value + coordChange, matrix->value + coordChange);
        }
    }

    free(timelyMult);
}
