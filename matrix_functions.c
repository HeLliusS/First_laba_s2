#include <stdio.h>
#include <stdlib.h>

#include "matrix_functions.h"

int setMatrixElem(Matrix* matrix, const int column, const int line, const void* value) {
    if (matrix == NULL || value == NULL)
        return MATRIX_ERR_NULL;

    if (matrix->value == NULL)
        return MATRIX_ERR_NULL;

    if (column >= matrix->length || column < 0 || line >= matrix->height || line < 0) {
        return MATRIX_ERR_BOUNDS;
    }

    matrix->info->set(value, (char*)matrix->value + (column + line * matrix->length) * matrix->info->elemSize);

    return MATRIX_OK;
}

int printMatrix(const Matrix* matrix) {
    if (matrix == NULL)
        return MATRIX_ERR_NULL;

    if (matrix->value == NULL)
        return MATRIX_ERR_NULL;

    int row = 0, col = 0;
    int offset = 0;

    for (row = 0; row < matrix->height; row++) {
        for (col = 0; col < matrix->length; col++) {
            offset = (col + row * matrix->length) * matrix->info->elemSize;
            matrix->info->print((char*)matrix->value + offset);

            if (col + 1 != matrix->length) printf(" ");
        }
        printf("\n");
    }

    return MATRIX_OK;
}

int sumMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if (first == NULL || second == NULL || newMatrix == NULL)
        return MATRIX_ERR_NULL;

    if (first->value == NULL || second->value == NULL)
        return MATRIX_ERR_NULL;

    if ((first->length != second->length) || (first->height != second->height)) {
        return MATRIX_ERR_SIZE;
    }

    if ((first->info != second->info)) {
        return MATRIX_ERR_TYPE;
    }

    int result = initMatrix(newMatrix, first->height, first->length, first->info);
    if (result != MATRIX_OK)
        return result;

    int row = 0, col = 0;
    int rowCount = first->height, colCount = first->length;
    int offset = 0;

    for (row = 0; row < rowCount; row++) {
        for (col = 0; col < colCount; col++) {
            offset = (col + row * colCount) * first->info->elemSize;
            first->info->add(((char*)first->value + offset),
                             ((char*)second->value + offset),
                             ((char*)newMatrix->value + offset));
        }
    }

    return MATRIX_OK;
}

int multMatrix(const Matrix* first, const Matrix* second, Matrix* newMatrix) {
    if (first == NULL || second == NULL || newMatrix == NULL)
        return MATRIX_ERR_NULL;

    if (first->value == NULL || second->value == NULL)
        return MATRIX_ERR_NULL;

    if ((first->length != second->height)) {
        return MATRIX_ERR_SIZE;
    }

    if ((first->info != second->info)) {
        return MATRIX_ERR_TYPE;
    }

    int result = initMatrix(newMatrix, first->height, second->length, first->info);
    if (result != MATRIX_OK)
        return result;

    int colRes = 0, rowRes = 0, k = 0;
    int offsetRes = 0, offsetFirst = 0, offsetSecond = 0;
    void* tempBuffer = malloc(newMatrix->info->elemSize);

    if (tempBuffer == NULL) {
        deleteMatrix(newMatrix);
        return MATRIX_ERR_MEMORY;
    }

    for (colRes = 0; colRes < newMatrix->length; colRes++) {
        for (rowRes = 0; rowRes < newMatrix->height; rowRes++) {
            offsetRes = (colRes + rowRes * newMatrix->length) * first->info->elemSize;
            newMatrix->info->set(newMatrix->info->neutralElemAdd, (char*)newMatrix->value + offsetRes);

            for (k = 0; k < first->length; k++) {
                offsetFirst = (rowRes * first->length + k) * first->info->elemSize;
                offsetSecond = (colRes + second->length * k) * first->info->elemSize;
                newMatrix->info->mult((char*)first->value + offsetFirst,
                                      (char*)second->value + offsetSecond,
                                      tempBuffer);

                newMatrix->info->add((char*)newMatrix->value + offsetRes,
                                     tempBuffer,
                                     (char*)newMatrix->value + offsetRes);
            }
        }
    }

    free(tempBuffer);
    return MATRIX_OK;
}

int transMatrix(const Matrix* matrix, Matrix* newMatrix) {
    if (matrix == NULL || newMatrix == NULL)
        return MATRIX_ERR_NULL;

    if (matrix->value == NULL)
        return MATRIX_ERR_NULL;

    int result = initMatrix(newMatrix, matrix->length, matrix->height, matrix->info);
    if (result != MATRIX_OK)
        return result;

    int rowNew = 0, colNew = 0;
    int offsetNew = 0, offsetOrig = 0;

    for (rowNew = 0; rowNew < newMatrix->height; rowNew++) {
        for (colNew = 0; colNew < newMatrix->length; colNew++) {
            offsetNew = (rowNew * newMatrix->length + colNew) * matrix->info->elemSize;
            offsetOrig = (colNew * matrix->length + rowNew) * matrix->info->elemSize;
            newMatrix->info->set((char*)matrix->value + offsetOrig,
                                 (char*)newMatrix->value + offsetNew);
        }
    }

    return MATRIX_OK;
}

int lineAddMatrix(Matrix* matrix, const int line, const void* cfs) {
    if (matrix == NULL || cfs == NULL)
        return MATRIX_ERR_NULL;

    if (matrix->value == NULL)
        return MATRIX_ERR_NULL;

    if (line > matrix->height || line < 1)
        return MATRIX_ERR_LINE;

    int srcRow = 0, col = 0;
    int offsetTarget = 0, offsetSrc = 0;
    void* tempBuffer = malloc(matrix->info->elemSize);

    if (tempBuffer == NULL)
        return MATRIX_ERR_MEMORY;

    for (srcRow = 0; srcRow < matrix->height; srcRow++) {
        for (col = 0; col < matrix->length; col++) {
            offsetTarget = ((line - 1) * matrix->length + col) * matrix->info->elemSize;
            offsetSrc = (srcRow * matrix->length + col) * matrix->info->elemSize;
            matrix->info->mult((char*)cfs + srcRow * matrix->info->elemSize,
                               (char*)matrix->value + offsetSrc,
                               tempBuffer);
            matrix->info->add(tempBuffer,
                              (char*)matrix->value + offsetTarget,
                              (char*)matrix->value + offsetTarget);
        }
    }

    free(tempBuffer);
    return MATRIX_OK;
}