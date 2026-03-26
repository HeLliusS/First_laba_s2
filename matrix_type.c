#include <stdio.h>
#include <stdlib.h>

#include "matrix_type.h"

void initMatrix(Matrix* matrix, const int height, const int length, const TypeInfo* info) {
    if (height * length <= 0) {
        printf("SizeError");
        return;
    }

    matrix->value = malloc(info->elemSize * height * length);

    if (matrix->value == NULL)
        return;

    matrix->info = info;
    matrix->height = height;
    matrix->length = length;

    for (int i = 0; i < height * length; i++) {
        info->set(info->neutralElemAdd, (char*)matrix->value + i * info->elemSize);
    }
}

void deleteMatrix(Matrix* matrix) {
    free(matrix->value);
    matrix->value = NULL;
}
