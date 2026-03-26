#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stddef.h>

typedef void (*BinaryOperation)(const void*, const void*, void*);

typedef void (*ConstantOperation)(const void*);

typedef void (*SetterOperation)(const void*, void*);

typedef struct TypeInfo {
    BinaryOperation add;
    BinaryOperation mult;
    ConstantOperation print;
    SetterOperation set;

    void* neutralElemAdd;

    size_t elemSize;
} TypeInfo;

#endif
