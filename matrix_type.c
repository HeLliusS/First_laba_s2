#include <stdio.h>
#include <stdlib.h>

#include "matrix_type.h"


int initMatrix(Matrix* matrix, const int height, const int length, const TypeInfo* info) {

    if (matrix == NULL || info == NULL)
        return MATRIX_ERR_NULL;

    if (height <= 0 || length <= 0)
        return MATRIX_ERR_SIZE;


    matrix->value = malloc(info->elemSize * height * length);

    if (matrix->value == NULL)
        return MATRIX_ERR_MEMORY;

    matrix->info = info;
    matrix->height = height;
    matrix->length = length;

    for (int i = 0; i < height * length; i++) {
        info->set(info->neutralElemAdd, (char*)matrix->value + i * info->elemSize);
    }

    return MATRIX_OK;
}

void deleteMatrix(Matrix* matrix) {
    if (matrix == NULL) return;
    free(matrix->value);
    matrix->value = NULL;
}
