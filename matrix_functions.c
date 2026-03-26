#include <stdio.h>
#include <stdlib.h>

#include "matrix_functions.h"

void setMatrixElem(Matrix* matrix, const int colon, const int line, const void* value) {
    if (matrix == NULL || value == NULL)
        return;

    if (matrix->value == NULL)
        return;

    if (colon > matrix->length || colon < 0 || line > matrix->height || line < 0) {
        printf("Coord is out of range");
        return;
    }

    matrix->info->set(value, (char*)matrix->value + (colon + line * matrix->length) * matrix->info->elemSize);
}

void printMatrix(const Matrix* matrix) {
    if (matrix  == NULL)
        return;

    if (matrix->value == NULL)
        return;

    int coordLength = 0, coordHeight = 0;
    int coord = 0;

    for (coordHeight = 0; coordHeight < matrix->height; coordHeight++) {
        for (coordLength = 0; coordLength < matrix->length; coordLength++) {
            coord = (coordLength + coordHeight * matrix->length) * matrix->info->elemSize;

            matrix->info->print((char*)matrix->value + coord);

            if (coordLength + 1 != matrix->length) printf(" ");
        }
        printf("\n");
    }
}

void sumMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if (first == NULL || second == NULL || newMatrix == NULL)
        return;

    if (first->value == NULL || second->value == NULL)
        return;

    if ((first->length != second->length) || (first->height != second->height)) {
        printf("Wrong size of Matrix");
        return;
    }

    if ((first->info != second->info)) {
        printf("Types of Matrix elements do not match");
        return;
    }

    initMatrix(newMatrix, first->height, first->length, first->info);

    if (newMatrix->value == NULL)
        return;

    int coordLength = 0, coordHeight = 0, length = first->length, height = first->height;
    int coord = 0;

    for (coordHeight = 0; coordHeight < height; coordHeight++) {
        for (coordLength = 0; coordLength < length; coordLength++) {
            coord = (coordLength + coordHeight * length) * first->info->elemSize;
            first->info->add(((char*)first->value + coord), ((char*)second->value + coord), ((char*)newMatrix->value + coord));
        }
    }
}

void multMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if (first == NULL || second == NULL || newMatrix == NULL)
        return;

    if (first->value == NULL || second->value == NULL)
        return;

    if ((first->length != second->height)) {
        printf("Wrong size of Matrix");
        return;
    }

    if ((first->info != second->info)) {
        printf("Types of Matrix elements do not match");
        return;
    }

    initMatrix(newMatrix, first->height, second->length, first->info);

    if (newMatrix->value == NULL)
        return;

    int coordNewLength = 0, coordNewHeight = 0, coordSlip = 0;
    int coord = 0, coordFirst = 0, coordSecond = 0;
    void* timelyMult = malloc(newMatrix->info->elemSize);

    if (timelyMult == NULL) {
        deleteMatrix(newMatrix);
        return;
    }

    for (coordNewLength = 0; coordNewLength < newMatrix->length; coordNewLength++) {
        for (coordNewHeight = 0; coordNewHeight < newMatrix->height; coordNewHeight++) {
            coord = (coordNewLength + coordNewHeight * newMatrix->length) * first->info->elemSize;
            newMatrix->info->set(newMatrix->info->neutralElemAdd, (char*)newMatrix->value + coord);

            for (coordSlip = 0; coordSlip < first->length; coordSlip++) {
                coordFirst = (coordNewHeight * first->length + coordSlip) * first->info->elemSize;
                coordSecond = (coordNewLength + second->length * coordSlip) * first->info->elemSize;
                newMatrix->info->mult((char*)first->value + coordFirst, (char*)second->value + coordSecond, timelyMult);

                newMatrix->info->add((char*)newMatrix->value + coord, timelyMult, (char*)newMatrix->value + coord);
            }
        }
    }

    free(timelyMult);
}

void transMatrix(const Matrix* matrix, Matrix* newMatrix) {
    if (matrix == NULL || newMatrix == NULL)
        return;

    if (matrix->value == NULL)
        return;

    initMatrix(newMatrix, matrix->length, matrix->height, matrix->info);

    if (newMatrix->value == NULL)
        return;

    int coordLengthNew = 0, coordHeightNew = 0;
    int coordNew = 0, coordMatrix = 0;

    for (coordHeightNew = 0; coordHeightNew < newMatrix->height; coordHeightNew++) {
        for (coordLengthNew = 0; coordLengthNew < newMatrix->length; coordLengthNew++) {
            coordNew = (coordHeightNew * newMatrix->length + coordLengthNew) * matrix->info->elemSize;
            coordMatrix = (coordLengthNew * matrix->length + coordHeightNew) * matrix->info->elemSize;
            newMatrix->info->set((char*)matrix->value + coordMatrix, (char*)newMatrix->value + coordNew);
        }
    }
}

void lineAddMatrix(Matrix* matrix, const int line, const void* cfs) {
    if (matrix == NULL || cfs == NULL)
        return;

    if (matrix->value == NULL)
        return;

    if (line > matrix->height || line < 1)
        return;

    int addLine = 0, addColon = 0;
    int coordChange = 0, coordGet = 0;
    void* timelyMult = malloc(matrix->info->elemSize);

    if (timelyMult == NULL)
        return;

    for (addLine = 0; addLine < matrix->height; addLine++) {
        for (addColon = 0; addColon < matrix->length; addColon++) {
            coordChange = ((line - 1) * matrix->length + addColon) * matrix->info->elemSize;
            coordGet = (addLine * matrix->length + addColon) * matrix->info->elemSize;
            matrix->info->mult((char*)cfs + addLine * matrix->info->elemSize, (char*)matrix->value + coordGet, timelyMult);
            matrix->info->add(timelyMult, (char*)matrix->value + coordChange, (char*)matrix->value + coordChange);
        }
    }

    free(timelyMult);
}
