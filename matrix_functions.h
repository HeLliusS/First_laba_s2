#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include "matrix_type.h"
#include "matrix_errors.h"

int setMatrixElem(Matrix*, int, int, const void*);

int printMatrix(const Matrix*);

int sumMatrix(const Matrix*, const Matrix*, Matrix*);

int multMatrix(const Matrix*, const Matrix*, Matrix*);

int transMatrix(const Matrix*, Matrix*);

int lineAddMatrix(Matrix*, int, const void*);

#endif
