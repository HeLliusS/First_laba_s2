#ifndef DOUBLE_TYPE_H
#define DOUBLE_TYPE_H

#include "type_info.h"

typedef struct Double {
    double value;
} Double;

void addDouble(const void*, const void*, void*);

void multDouble(const void*, const void*, void*);

void printDouble(const void*);

void setDouble(const void*, void*);

const TypeInfo* getDoubleTypeInfo();
void deleteDoubleTypeInfo();

#endif
