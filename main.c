#include <stdio.h>

#include "double_type.h"
#include "integer_type.h"
#include "matrix_functions.h"

int main() {

    Matrix one, two, three;

    initMatrix(&one, 4, 4, getIntegerTypeInfo());
    initMatrix(&two, 4, 4, getIntegerTypeInfo());

    Integer timely;
    timely.value = 0;
    int i = 0, j = 0;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            timely.value++;

            setMatrixElem(&one, j, i, (void*)&timely);
            setMatrixElem(&two, j, i, (void*)&timely);
        }
    }

    printMatrix(&one);

    printf("\n");

    printMatrix(&two);

    printf("\n");

    sumMatrix(&one, &two, &three);


    printMatrix(&three);

    deleteMatrix(&three);

    printf("\n");

    multMatrix(&one, &two, &three);

    printMatrix(&three);

    deleteMatrix(&three);

    printf("\n");

    transMatrix(&one, &three);

    printMatrix(&three);

    deleteMatrix(&three);

    printf("\n");

    printMatrix(&one);

    printf("\n");

    Integer coefs[4];

    coefs[0].value = 2;
    coefs[1].value = 0;
    coefs[2].value = -1;
    coefs[3].value = 1;

    lineAddMatrix(&one, 1, (void*)coefs);

    printMatrix(&one);

    deleteMatrix(&one);
    deleteMatrix(&two);

    deleteIntegerTypeInfo();

    initMatrix(&one, 3, 3, getDoubleTypeInfo());

    Double t = {1.0};

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            t.value = t.value + 1;

            setMatrixElem(&one, j, i, (void*)&t);
        }
    }

    printf("%d %d %d\n", sizeof(Integer), sizeof(Double), sizeof(void*));

    printMatrix(&one);

    deleteMatrix(&one);
    deleteDoubleTypeInfo();

    return 0;
}