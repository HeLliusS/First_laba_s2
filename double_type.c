#include <stdio.h>
#include <stdlib.h>

#include "double_type.h"

void addDouble(const void* const first, const void* const second, void* const result) {
    Double* sumDouble = (Double*)result;

    const Double* const firstDouble = (const Double*)first;
    const Double* const secondDouble = (const Double*)second;

    sumDouble->value = firstDouble->value + secondDouble->value;
}

void multDouble(const void* const first, const void* const second, void* const result) {
    Double* multDouble = (Double*)result;

    const Double* const firstDouble = (const Double*)first;
    const Double* const secondDouble = (const Double*)second;

    multDouble->value = firstDouble->value * secondDouble->value;
}

void printDouble(const void* elem) { printf("%lf", ((Double*)elem)->value); }

void setDouble(const void* value, void* elem) { ((Double*)elem)->value = ((Double*)value)->value; }



static TypeInfo* doubleTypeInfo = NULL;

const TypeInfo* getDoubleTypeInfo() {
    if (doubleTypeInfo == NULL) {
        doubleTypeInfo = malloc(sizeof(TypeInfo));

        if (doubleTypeInfo == NULL)
            return NULL;

        doubleTypeInfo->neutralElemAdd = malloc(sizeof(Double));

        if (doubleTypeInfo->neutralElemAdd == NULL) {
            free(doubleTypeInfo);
            doubleTypeInfo = NULL;
            return NULL;
        }

        doubleTypeInfo->add = addDouble;
        doubleTypeInfo->mult = multDouble;
        doubleTypeInfo->print = printDouble;
        doubleTypeInfo->set = setDouble;

        doubleTypeInfo->elemSize = sizeof(Double);

        ((Double*)(doubleTypeInfo->neutralElemAdd)) -> value = 0.0;
    }

    return doubleTypeInfo;
}

void deleteDoubleTypeInfo() {
    if (doubleTypeInfo != NULL) {
        free(doubleTypeInfo->neutralElemAdd);

        free(doubleTypeInfo);
        doubleTypeInfo = NULL;
    }
}
