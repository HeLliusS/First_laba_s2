#ifndef INTEGER_TYPE_H
#define INTEGER_TYPE_H

#include "type_info.h"

typedef struct Integer {
    int value;
} Integer;

void addInteger(const void*, const void*, void*);

void multInteger(const void*, const void*, void*);

void printInteger(const void*);

void setInteger(const void*, void*);

const TypeInfo* getIntegerTypeInfo();
void deleteIntegerTypeInfo();

#endif
