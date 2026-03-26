#include <stdio.h>
#include <stdlib.h>

#include "integer_type.h"

void addInteger(const void* const first, const void* const second, void* const result) {
    Integer* sumInt = (Integer*)result;

    const Integer* const firstInt = (const Integer*)first;
    const Integer* const secondInt = (const Integer*)second;

    sumInt->value = firstInt->value + secondInt->value;
}

void multInteger(const void* const first, const void* const second, void* const result) {
    Integer* multInt = (Integer*)result;

    const Integer* const firstInt = (const Integer*)first;
    const Integer* const secondInt = (const Integer*)second;

    multInt->value = firstInt->value * secondInt->value;
}

void printInteger(const void* elem) { printf("%d", ((Integer*)elem)->value); }

void setInteger(const void* value, void* elem) { ((Integer*)elem)->value = ((Integer*)value)->value; }



static TypeInfo* integerTypeInfo = NULL;

const TypeInfo* getIntegerTypeInfo() {
    if (integerTypeInfo == NULL) {
        integerTypeInfo = malloc(sizeof(TypeInfo));

        if (integerTypeInfo == NULL)
            return NULL;

        integerTypeInfo->neutralElemAdd = malloc(sizeof(Integer));

        if (integerTypeInfo->neutralElemAdd == NULL) {
            free(integerTypeInfo);
            integerTypeInfo = NULL;
            return NULL;
        }

        integerTypeInfo->add = addInteger;
        integerTypeInfo->mult = multInteger;
        integerTypeInfo->print = printInteger;
        integerTypeInfo->set = setInteger;

        integerTypeInfo->elemSize = sizeof(Integer);

        ((Integer*)(integerTypeInfo->neutralElemAdd)) -> value = 0;
    }

    return integerTypeInfo;
}

void deleteIntegerTypeInfo() {
    if (integerTypeInfo != NULL) {
        free(integerTypeInfo->neutralElemAdd);

        free(integerTypeInfo);
        integerTypeInfo = NULL;
    }
}
