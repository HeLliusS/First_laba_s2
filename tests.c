#include <assert.h>
#include <stdbool.h>

#include "matrix_functions.h"
#include "integer_type.h"

void testSetter() {
    Matrix check, right;
    Integer n = {0};
    bool k = true;
    int i, j;

    initMatrix(&check, 3, 3, getIntegerTypeInfo());
    initMatrix(&right, 3, 3, getIntegerTypeInfo());

    for(i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            n.value = i * 3 + j + 1;
            right.info->set(&n, right.value + (j + i * right.length) * sizeof(void*));
        }

    for(i = 0; i < 3; i++)
        for (j = 0; j < 3; j++) {
            n.value = i * 3 + j + 1;
            setMatrixElem(&check, j, i, &n);
        }

    for(i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (((Integer*)(right.value + (j + i * right.length)))->value != ((Integer*)(check.value + (j + i * check.length)))->value) {

                k = false;
                break;
            }

    deleteMatrix(&right);
    deleteMatrix(&check);

    assert(k);
}

void testSumMatrix() {

    Matrix first, second, third;

    int i, j;
    Integer res[16];
    Integer valueFirst, valueSecond;
    bool k = true;


    initMatrix(&first, 4, 4, getIntegerTypeInfo());
    initMatrix(&second, 4, 4, getIntegerTypeInfo());

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            valueFirst.value = i * 4 + j + 1;
            valueSecond.value = j * 4 + i;

            res[i * 4 + j].value = valueFirst.value + valueSecond.value;

            setMatrixElem(&first, j, i, &valueFirst);
            setMatrixElem(&second, j, i, &valueSecond);
        }
    }

    sumMatrix(&first, &second, &third);

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (((Integer*)(third.value + (i * 4 + j) * sizeof(void*)))->value != res[i * 4 + j].value) {
                k = false;
                break;
            }
        }
    }

    assert(k);
}
