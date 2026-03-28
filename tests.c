#include <assert.h>
#include <stdlib.h>

#include "matrix_functions.h"
#include "integer_type.h"
#include "double_type.h"

void test_init_invalid_sizes() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix m;

    int ret = initMatrix(&m, 0, 5, info);
    assert(ret == MATRIX_ERR_SIZE);
    ret = initMatrix(&m, -2, 3, info);
    assert(ret == MATRIX_ERR_SIZE);
    ret = initMatrix(&m, 2, -3, info);
    assert(ret == MATRIX_ERR_SIZE);
}

void test_init_delete() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix m;

    int ret = initMatrix(&m, 2, 3, info);
    assert(ret == MATRIX_OK);
    assert(m.value != NULL);
    assert(m.height == 2);
    assert(m.length == 3);
    assert(m.info == info);

    deleteMatrix(&m);
    assert(m.value == NULL);
}

void test_set_elem() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix m;
    initMatrix(&m, 2, 2, info);

    Integer val1 = {5};
    Integer val2 = {7};

    int ret = setMatrixElem(&m, 0, 0, &val1);
    assert(ret == MATRIX_OK);
    ret = setMatrixElem(&m, 1, 1, &val2);
    assert(ret == MATRIX_OK);

    ret = setMatrixElem(&m, 2, 0, &val1);
    assert(ret == MATRIX_ERR_BOUNDS);
    ret = setMatrixElem(&m, 0, 2, &val1);
    assert(ret == MATRIX_ERR_BOUNDS);

    deleteMatrix(&m);
}

void test_sum() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix a, b, c;

    initMatrix(&a, 2, 2, info);
    initMatrix(&b, 2, 2, info);

    Integer vals[4] = {{1},{2},{3},{4}};
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            setMatrixElem(&a, j, i, &vals[i*2 + j]);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 2; ++j)
            setMatrixElem(&b, j, i, &vals[i*2 + j]);

    int ret = sumMatrix(&a, &b, &c);
    assert(ret == MATRIX_OK);

    deleteMatrix(&a);
    deleteMatrix(&b);
    deleteMatrix(&c);
}

void test_mult() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix a, b, c;

    initMatrix(&a, 2, 2, info);
    initMatrix(&b, 2, 2, info);
    Integer val_a[4] = {{1},{2},{3},{4}};
    Integer val_b[4] = {{5},{6},{7},{8}};
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            setMatrixElem(&a, j, i, &val_a[i*2 + j]);
            setMatrixElem(&b, j, i, &val_b[i*2 + j]);
        }
    }

    int ret = multMatrix(&a, &b, &c);
    assert(ret == MATRIX_OK);

    deleteMatrix(&a);
    deleteMatrix(&b);
    deleteMatrix(&c);
}

void test_trans() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix m, t;

    initMatrix(&m, 2, 3, info);
    int k = 1;
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            Integer val = {k++};
            setMatrixElem(&m, j, i, &val);
        }

    int ret = transMatrix(&m, &t);
    assert(ret == MATRIX_OK);

    deleteMatrix(&m);
    deleteMatrix(&t);
}

void test_line_add() {
    const TypeInfo* info = getIntegerTypeInfo();
    Matrix m;

    initMatrix(&m, 3, 3, info);
    int k = 1;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) {
            Integer val = {k++};
            setMatrixElem(&m, j, i, &val);
        }

    Integer coeffs[3] = {{1},{2},{3}};
    int ret = lineAddMatrix(&m, 2, coeffs);
    assert(ret == MATRIX_OK);

    deleteMatrix(&m);
}

void test_error_conditions() {
    const TypeInfo* intInfo = getIntegerTypeInfo();
    const TypeInfo* doubleInfo = getDoubleTypeInfo();

    Matrix a, b, c;

    // Разные типы
    initMatrix(&a, 2, 2, intInfo);
    initMatrix(&b, 2, 2, doubleInfo);
    int ret = sumMatrix(&a, &b, &c);
    assert(ret == MATRIX_ERR_TYPE);
    ret = multMatrix(&a, &b, &c);
    assert(ret == MATRIX_ERR_TYPE);
    deleteMatrix(&a);
    deleteMatrix(&b);

    // Неправильные размеры для сложения
    initMatrix(&a, 2, 3, intInfo);
    initMatrix(&b, 2, 2, intInfo);
    ret = sumMatrix(&a, &b, &c);
    assert(ret == MATRIX_ERR_SIZE);
    deleteMatrix(&a);
    deleteMatrix(&b);

    // Неправильные размеры для умножения
    initMatrix(&a, 2, 3, intInfo);
    initMatrix(&b, 2, 2, intInfo);
    ret = multMatrix(&a, &b, &c);
    assert(ret == MATRIX_ERR_SIZE);
    deleteMatrix(&a);
    deleteMatrix(&b);

    // Передача NULL
    ret = sumMatrix(NULL, &b, &c);
    assert(ret == MATRIX_ERR_NULL);
    ret = multMatrix(&a, NULL, &c);
    assert(ret == MATRIX_ERR_NULL);
    ret = transMatrix(NULL, &c);
    assert(ret == MATRIX_ERR_NULL);
    ret = lineAddMatrix(NULL, 1, NULL);
    assert(ret == MATRIX_ERR_NULL);
}

int main() {
    test_init_invalid_sizes();
    test_init_delete();
    test_set_elem();
    test_sum();
    test_mult();
    test_trans();
    test_line_add();
    test_error_conditions();

    deleteIntegerTypeInfo();
    deleteDoubleTypeInfo();

    return 0;
}