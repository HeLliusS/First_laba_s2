#ifndef MATRIX_TYPE_H
#define MATRIX_TYPE_H

#include "type_info.h"

typedef struct Matrix {
    void* value;
    int height;
    int length;
    const TypeInfo* info;
} Matrix;

void initMatrix(Matrix*, int, int, const TypeInfo*);

void deleteMatrix(Matrix*);

#endif
