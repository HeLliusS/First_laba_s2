#include <stdio.h>
#include <stdlib.h>

#include "matrix_type.h"

void initMatrix(Matrix* new, const int height, const int length, const TypeInfo* info) {
    if (height * length <= 0) {
        printf("SizeError");
        return;
    }

    new->info = info;
    new->height = height;
    new->length = length;
    new->value = malloc(sizeof(void*) * height * length);
}

void deleteMatrix(Matrix* matrix) { free(matrix->value); }
