#ifndef MATRIX_FUNCTIONS_H
#define MATRIX_FUNCTIONS_H

#include "matrix_type.h"

void setMatrixElem(Matrix*, int, int, void*);

void printMatrix(const Matrix*);

void sumMatrix(const Matrix*, const Matrix*, Matrix*);

void multMatrix(const Matrix*, const Matrix*, Matrix*);

void transMatrix(const Matrix*, Matrix*);

void lineAddMatrix(Matrix*, int, void*);

#endif
